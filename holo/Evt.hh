#pragma once
#include <holo/stdPrimitives.hh>
#include <holo/boostPrimitives.hh>
namespace holo {
  typedef unsigned int CallbackID;
  /**
   * \brief Abstract "event" dispatcher.
   * \param Types... list of parameter types used in dispatching
   */
  template<typename... Types>
  class EvtAbstract {
    public:
      /** \depreciated */
      using sPtr = shared_ptr<EvtAbstract<Types...>>;

      typedef std::function<void(CallbackID, Types...)> CallbackFunctionWithID;
      typedef std::function<void(Types...)>             CallbackFunction;
      /** map of IDs to their callbacks. */
      typedef std::map<CallbackID, CallbackFunction>    CallbackMap;

    private:
      /** \brief Every handler registered is given an ID. */
      CallbackID  nextId{ 0 }, erasedCount{ 0 };
      CallbackMap registeredOnce;
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
      virtual CallbackID Once(CallbackFunction handler) {
        CallbackID id      = nextId++;
        registeredOnce[id] = handler;
        return id;
      }

      /** \brief Removes a callback from the list to be triggered.
       * \param id integer returned by `On` when registering the handler.
       */
      virtual void Off(CallbackID id) { registered.erase(id); };
      virtual void Clear() { registered.clear(); };

      void TriggerMap(CallbackMap& mapList, Types... eventData ) {
        for (auto pair : mapList){
          pair.second(eventData...);
        }
      }

      /** \brief Call all registered handlers passing all parameters that were provided.
       * \note Once callbacks are not triggered via const calls.
       */
      virtual void Trigger(Types... eventData) {
        TriggerMap(registered, eventData...);
        TriggerMap(registeredOnce, eventData...);
      }
      /** \brief Simply an alias for `Trigger`, making the class usable as a `Handler` */
      void operator()(Types... eventData) { return this->Trigger(eventData...); }

    protected:
  };
  /** Dispatcher with zero parameters.*/
  typedef EvtAbstract<> EvtVoid;

  /** Provide base, non-void implementation.
   * \note Provides `VOID`, a linked AbstractDispatcher attached to this event
   * that is always triggered with this event but does not take any arguments.
   */
  template<typename TypeName, typename... MoreTypes>
  class EvtAbstractType : public EvtAbstract<TypeName, MoreTypes...> {
    public:
      /** shared pointer for this type of dispatcher */
      using sPtr = std::shared_ptr<EvtAbstractType<TypeName, MoreTypes...>>;
      EvtVoid::sPtr VOID{ std::make_shared<EvtVoid>() };
      // virtual CallbackID   On(VoidDispatcher::CallbackFunction callback) {
      //   return VOID->On(callback);
      // };
      /** Mix void and non-void phases of VOID: */
      virtual void  Trigger(TypeName data, MoreTypes... eventData) override {
        EvtAbstract<TypeName, MoreTypes...>::Trigger(data, eventData...);
        VOID->Trigger();
      };
      /** Dispatches off signals to self and VOID sub handler */
      virtual void Off(CallbackID id) override {
        EvtAbstract<TypeName, MoreTypes...>::Off(id);
        VOID->Off(id);
      }

    protected:
  };
  /** Provide a framework for switching on simple types.
   * \note Must provide override of `ExtractSwitch`.
   * \details SwitchType is used as key to map of `AbstractDispatch<Types...>` handlers,
   * on `Trigger(Types...)` use provided `ExtractSwitch` to distill the complex event into a value
   * used to look up handler. If defined dispatch. Always dispatches local handlers.
   */
  template<typename SwitchType, typename TypeName, typename... MoreTypes>
  class EvtAbstractTypeSwitch : public EvtAbstractType<TypeName, MoreTypes...> {
    public:
      /** \deprecated **/
      using sPtr = std::shared_ptr<EvtAbstractTypeSwitch<SwitchType, TypeName, MoreTypes...>>;
      /** \todo give this a better name. */
      using SpecialHandlers_t =
        std::map<SwitchType, std::shared_ptr<EvtAbstract<TypeName, MoreTypes...>>>;
      /** \todo give this a better name. */
      SpecialHandlers_t SpecialHandlers;

      // EvtAbstractTypeSwitch(SpecialHandlers_t h)
      //   : SpecialHandlers{ h } {}
      virtual SwitchType ExtractSwitch(TypeName, MoreTypes...) const = 0;
      virtual void       Trigger(TypeName data, MoreTypes... eventData) {
        SwitchType switchVal = ExtractSwitch(data, eventData...);
        if (SpecialHandlers.contains(switchVal)) {
          SpecialHandlers.at(switchVal)->Trigger(data, eventData...);
        }
        EvtAbstractType<TypeName, MoreTypes...>::Trigger(data, eventData...);
      }
      virtual void Off(CallbackID id) override {
        EvtAbstractType<TypeName, MoreTypes...>::Off(id);
        for (auto pair : SpecialHandlers) {
          if (pair.second) {
            pair.second->Off(id);
          }
        }
      }
  };
}