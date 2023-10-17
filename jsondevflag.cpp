#include "jsondevflag.h"

JsonDevFlag::JsonDevFlag()
{

}
class JsonDevFlag extends LocalStorageDevFlag {
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
    if (void 0 !== e) try {
      return JSON.parse(e);
    } catch (z) {
      return;
    }
  }
  set(e) {
    this.write(JSON.stringify(e));
  }
  prop(e) {
    if (void 0 !== this.value) return this.value[e];
  }
}
