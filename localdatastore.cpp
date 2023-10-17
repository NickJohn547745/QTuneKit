#include "localdatastore.h"

LocalDataStore::LocalDataStore()
{

}
class LocalDataStore {
  get hasDataStore() {
    return this.enableDataStore && void 0 !== this._store;
  }
  delete(e, n) {
    this.hasDataStore && this._store.remove(e, n);
  }
  read(e, n, d, h) {
    h || "function" != typeof d || (h = d, d = void 0);
    const p = {};
    let y = false;
    if (d && (y = Object.keys(d).some(e => /^(fields|extend)/.test(e)), d.views && (p.views = d.views), d.include && (p.relationships = d.include)), this.hasDataStore && !y) {
      let h, y = [];
      if (d && (y = Object.keys(d).reduce((e, n) => (-1 === bc.indexOf(n) && e.push([n, d[n]]), e), y)), h = y && 1 === y.length ? this._store.query(y[0][0], y[0][1]) : this._store.peek(e, n, p), Array.isArray(h)) {
        if (!d && h.length) return h;
      } else if (h) return h;
    }
    if ("function" == typeof h) return h();
  }
  write(e) {
    return this._prepareDataForDataStore(e, e => this._store.save(e));
  }
  parse(e) {
    return this._prepareDataForDataStore(e, e => this._store.populateDataRecords(e, {}));
  }
  _prepareDataForDataStore(e, n) {
    return this.hasDataStore ? Array.isArray(e) ? n({data: e}) : Object.keys(e).reduce((d, h) => {
      const p = e[h];
      return Object.prototype.hasOwnProperty.call(Object(p), "data") && (d[h] = n({data: p.data})), "meta" === h && (d[h] = e[h]), d;
    }, {}) : e;
  }
  constructor(e = {}) {
    this.enableDataStore = false;
    let n = false;
    e.features && Object.prototype.hasOwnProperty.call(Object(e.features), "api-data-store") && (this.enableDataStore = !!e.features["api-data-store"]), e.features && Object.prototype.hasOwnProperty.call(Object(e.features), "disable-data-store-record-reuse") && (n = !!e.features["disable-data-store-record-reuse"]), this.enableDataStore && (this._store = e.store || new DataStore({shouldDisableRecordReuse: n}), this._store.mapping = transformStoreData);
  }
}
