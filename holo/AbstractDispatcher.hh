#pragma once
#include <holo/stdPrimitives.hh>
namespace holo {
  typedef unsigned int CallbackID;
  /**
   * \brief Abstract "event" dispatcher.
   * \param Types... list of parameter types used in dispatching
   */
  template<typename... Types>
  class AbstractDispatcher {
    public:
      /** */
      using sPtr = shared_ptr<AbstractDispatcher<Types...>>;
      typedef std::function<void(Types...)> CallbackFunction;

      typedef std::map<CallbackID, CallbackFunction> CallbackMap;

    private:
      /** \brief Every handler registered is given an ID. */
      CallbackID  nextId{ 0 }, erasedCount{ 0 };
      CallbackMap registered;

    public:
      /** \brief Register a callback to be used when `Trigger` is called.
       * \param handler Callback to add.
       * \return integer id value, for use if `handler` needs to be later removed.
       */
      virtual CallbackID On(CallbackFunction handler) {
        CallbackID id  = nextId++;
        registered[id] = handler;
        return id;
      };

      /** \brief Removes a callback from the list to be triggered.
       * \param id integer returned by `On` when registering the handler.
       */
      virtual void Off(CallbackID id) { registered.erase(id); };
      virtual void Clear(){registered.clear();};
      /** \brief Call all registered handlers passing all parameters that were provided.
       */
      virtual void Trigger(Types... eventData) const {
        for (std::pair<CallbackID, CallbackFunction> pair : registered) {
          pair.second(eventData...);
        }
      };
      /** \brief Simply an alias for `Trigger`, making the class usable as a `Handler` */
      void operator()(Types... eventData) const { return this->Trigger(eventData...); }

    protected:
  };
  /** Dispatcher with zero parameters.*/
  typedef AbstractDispatcher<> VoidDispatcher;

  /** Provide base, non-void implementation.
   * \note Provides `VOID`, a linked AbstractDispatcher attached to this event
   * that is always triggered with this event but does not take any arguments.
   */
  template<typename TypeName, typename... MoreTypes>
  class TypeDispatcher : public AbstractDispatcher<TypeName, MoreTypes...> {
    public:
      /** shared pointer for this type of dispatcher */
      using sPtr = std::shared_ptr<TypeDispatcher<TypeName, MoreTypes...>>;
      VoidDispatcher::sPtr VOID{ std::make_shared<VoidDispatcher>() };
      //virtual CallbackID   On(VoidDispatcher::CallbackFunction callback) {
      //  return VOID->On(callback);
      //};
      /** Mix void and non-void phases of VOID: */
      virtual void Trigger(TypeName data, MoreTypes... eventData) const override {
        AbstractDispatcher<TypeName, MoreTypes...>::Trigger(data, eventData...);
        VOID->Trigger();
      };

    protected:
  };
  /** Provide a framework for switching on simple types.
   * \note Must provide override of `ExtractSwitch`.
   * \details SwitchType is used as key to map of `AbstractDispatch<Types...>` handlers,
   * on `Trigger(Types...)` use provided `ExtractSwitch` to distill the complex event into a value
   * used to look up handler. If defined dispatch. Always dispatches local handlers.
   */
  template<typename SwitchType, typename TypeName, typename... MoreTypes>
  class AbstractSpecialer : public TypeDispatcher<TypeName, MoreTypes...> {
    public:
      using sPtr              = std::shared_ptr<AbstractSpecialer<SwitchType, TypeName, MoreTypes...>>;
      using SpecialHandlers_t = std::map<SwitchType, std::shared_ptr<AbstractDispatcher<TypeName, MoreTypes...>>>;
      SpecialHandlers_t SpecialHandlers;

      // AbstractSpecialer(SpecialHandlers_t h)
      //   : SpecialHandlers{ h } {}
      virtual SwitchType ExtractSwitch(TypeName, MoreTypes...) const = 0;
      virtual void       Trigger(TypeName data, MoreTypes... eventData) {
        SwitchType switchVal = ExtractSwitch(data, eventData...);
        if (SpecialHandlers.contains(switchVal)) {
          SpecialHandlers.at(switchVal)->Trigger(data, eventData...);
        }
        TypeDispatcher<TypeName, MoreTypes...>::Trigger(data, eventData...);
      }
  };
}