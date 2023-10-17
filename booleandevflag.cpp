#include "booleandevflag.h"

BooleanDevFlag::BooleanDevFlag()
{

}
class BooleanDevFlag extends LocalStorageDevFlag {
  static register(e) {
    return findOrCreate(e, this);
  }
  static get(e) {
    return this.register(e).get();
  }
  static set(e, n) {
    this.register(e).set(n);
  }
  get() {
    const e = this.read();
    if (void 0 !== e) return "1" === e || "true" === e.toLowerCase();
  }
  set(e) {
    "boolean" == typeof e ? this.write(true === e ? "1" : "0") : console.warn("Value for BooleanDevFlag should be a boolean");
  }
  get enabled() {
    return true === this.get();
  }
  enable() {
    this.set(true);
  }
  disable() {
    this.set(false);
  }
  toggle() {
    this.set(!this.get());
  }
}
