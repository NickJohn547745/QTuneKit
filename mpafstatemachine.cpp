#include "mpafstatemachine.h"

MPAFStateMachine::MPAFStateMachine()
{

}
class MPAFStateMachine {
  get currentState() {
    return this.machineService.state;
  }
  get currentStateName() {
    return this.currentState.value;
  }
  matches(e) {
    return this.machineService.state.matches(e);
  }
  transition(e, n) {
    const d = deriveTransitionEvent(e);
    if (false === d) return this.currentStateName;
    if (this.machineService.send(d), this.matches("error")) throw new Error(this.machineService.state.context.errorMessage);
    return this.currentStateName;
  }
  constructor() {
    this.machine = s({id: "mpaf", initial: "idle", context: {}, states: {error: {}, idle: {on: {play: "playing", stop: "idle", scrubBegin: {target: "scrubbing", actions: o(e => _objectSpreadProps$h(_objectSpread$u({}, e), {stateBeforeScrub: "idle"}))}, scrubEnd: {target: "error", actions: ["clearStateBeforeScrub", "setScrubEndError"]}}}, playing: {on: {scrubBegin: {target: "scrubbing", actions: o(e => _objectSpreadProps$h(_objectSpread$u({}, e), {stateBeforeScrub: "playing"}))}, stop: "idle", scrubEnd: {target: "error", actions: ["clearStateBeforeScrub", "setScrubEndError"]}}}, scrubbing: {on: {scrubEnd: [{target: "idle", cond: ({stateBeforeScrub: e}) => "idle" === e, actions: ["clearStateBeforeScrub"]}, {target: "playing", actions: ["clearStateBeforeScrub"]}]}}}}, {actions: {clearStateBeforeScrub: o(e => _objectWithoutProperties$2(e, ["stateBeforeScrub"])), setScrubEndError: o(e => _objectSpreadProps$h(_objectSpread$u({}, e), {errorMessage: "The scrub() method was called with the SCRUB_END action without a previous SCRUB_START descriptor"}))}}), this.machineService = v(this.machine).start();
  }
}
