#include "stringdevflag.h"

StringDevFlag::StringDevFlag()
{

}
class StringDevFlag extends LocalStorageDevFlag {
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
    return this.read();
  }
  set(e) {
    "string" != typeof e && console.warn("Value for StringDevFlag should be a string"), this.write(e);
  }
}
