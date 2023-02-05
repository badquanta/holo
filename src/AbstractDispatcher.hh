#pragma once
#include <functional>
#include <map>
#include <memory>
namespace holo {
  /**
   * \brief Abstract "event" dispatcher.
   * \param Types... list of parameter types used in dispatching
   */
  template<typename... Types>
  class AbstractDispatcher {
    public:
      /** */
      using Handler = std::function<void(Types...)>;

    private:
      /** \brief Every handler registered is given an ID. */
      int                    nextId = 0;
      //
      std::map<int, Handler> handlers;

    public:
      /** \brief Register a callback to be used when `Trigger` is called.
       * \param handler Callback to add.
       * \return integer id value, for use if `handler` needs to be later removed.
       */
      int On(Handler handler) {
        int id       = nextId++;
        handlers[id] = handler;
        return id;
      };
      /** \brief Removes a callback from the list to be triggered.
       * \param id integer returned by `On` when registering the handler.
       */
      void         Off(int id) { handlers.erase(id); };
      /** \brief Call all registered handlers passing all parameters that were provided. */
      virtual void Trigger(Types... eventData) const {
        for (auto pair : handlers) {
          pair.second(eventData...);
        }
      }
      /** \brief Simply an alias for `Trigger`, making the class usable as a `Handler` */
      void operator()(Types... eventData) const { return this->Trigger(eventData...); }
  };
  /** \brief An event dispatcher without any event parameters. */
  class VoidEvent : public AbstractDispatcher<> {
    public:
      using sPtr = std::shared_ptr<VoidEvent>;
  };
  template<typename... Types>
  class BaseDispatcher : public AbstractDispatcher<Types...> {
    public:
      /** shared pointer for this type of dispatcher */
      using sPtr = std::shared_ptr<BaseDispatcher>;
      std::shared_ptr<AbstractDispatcher<>> VOID{ std::make_shared<AbstractDispatcher<>>() };
      virtual void Trigger(Types... eventData) const override {
        AbstractDispatcher<Types...>::Trigger(eventData...);
        VOID->Trigger();
      }
  };
  template<typename SwitchType, typename... Types>
  class AbstractSpecializer : public BaseDispatcher<Types...> {
    public:
      using SpecialHandlers_t = std::map<SwitchType, std::shared_ptr<AbstractDispatcher<Types...>>>;
      SpecialHandlers_t  SpecialHandlers;

      // AbstractSpecializer(SpecialHandlers_t h)
      //   : SpecialHandlers{ h } {}
      virtual SwitchType ExtractSwitch(Types...) const = 0;
      virtual void       Trigger(Types... eventData) {
        SwitchType switchVal = ExtractSwitch(eventData...);
        if (SpecialHandlers.contains(switchVal)) {
          SpecialHandlers.at(switchVal)->Trigger(eventData...);
        }
        AbstractDispatcher<Types...>::Trigger(eventData...);
      }
  };
}