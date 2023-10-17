#include "networkcache.h"

NetworkCache::NetworkCache()
{

}
class NetworkCache {
  getItem(e) {
    const n = this.cacheKeyForPath(e), d = this.storage.getItem(n);
    if (null !== d) {
      const {x: e, d: h} = JSON.parse(d);
      if (e > Date.now()) return h;
      this.storage.removeItem(n);
    }
  }
  setItem(e, n, d = this.ttl) {
    const h = this.cacheKeyForPath(e);
    this.storage.setItem(h, JSON.stringify({x: Date.now() + d, d: n}));
  }
  removeItem(e) {
    const n = this.cacheKeyForPath(e);
    this.storage.removeItem(n);
  }
  removeItemsMatching(e, n = true) {
    const d = this.cacheKeyForPath(e);
    this.removeItemsMatchingCacheKey(d, n);
  }
  clear() {
    this.removeItemsMatchingCacheKey(this.prefix, false);
  }
  removeItemsMatchingCacheKey(e, n) {
    const d = new RegExp(`^${e}${n ? "$" : ""}`);
    (this.storage instanceof GenericStorage ? this.storage.keys : Object.keys(this.storage)).forEach(e => {
      e && d.test(e) && this.storage.removeItem(e);
    });
  }
  cacheKeyForPath(e) {
    return this.cacheKeyFunction(e, this.prefix);
  }
  constructor(e = {}) {
    this.storage = e.storage || new GenericStorage, this.prefix = e.prefix || "ï£¿", this.ttl = e.ttl || 3e5, this.cacheKeyFunction = e.cacheKeyFunction || DEFAULT_CACHE_KEY_FUNCTION;
  }
}
