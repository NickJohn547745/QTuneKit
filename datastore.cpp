#include "datastore.h"

DataStore::DataStore()
{

}
class DataStore extends Notifications {
  get mapping() {
    return this._mapping;
  }
  set mapping (e) {
    this._mapping = e;
  }
  clear() {
    this._records = {}, this._expiryRecords = new Set;
  }
  peek(e, n, d) {
    if (this._checkForExpiredRecords(), !this._records[e]) return n ? null : [];
    if (!n) return Object.values(this._records[e]);
    if (Array.isArray(n)) return n.map(n => {
      const h = this._records[e][n];
      if (h && h.hasProperties(d)) return h;
    });
    const h = this._records[e][n];
    return h && h.hasProperties(d) ? h : null;
  }
  populateDataRecords(e, n = {}, d = {}) {
    if (!e.data) return [];
    if (!Array.isArray(e.data)) return this.populateDataRecord(e.data, n, d);
    const h = [];
    return e.data.forEach((e, p) => {
      const y = _objectSpreadProps$q(_objectSpread$G({}, d), {parents: d.parents ? [_objectSpreadProps$q(_objectSpread$G({}, d.parents[0]), {position: p})] : []});
      d.parents && (d.parents[0].position = p);
      const m = this.populateDataRecord(e, n, y);
      h.push(m);
    }), h;
  }
  populateDataRecord(e, n = {}, d) {
    const h = d.filter || this.filter, p = d.mapping || this.mapping;
    if (h && !h(e)) return;
    if (p) {
      let n = "function" == typeof p ? p(e) : transform$8(p, e);
      Object.assign(e, n);
    }
    this._shouldDisableRecordReuse && (n = {});
    const y = this._materializeRecord(n, _objectSpread$G({id: e.id, type: e.type}, d));
    return e.meta && (y._meta = e.meta), e.attributes && e.attributes.cachingPolicy && e.attributes.cachingPolicy.maxAge && (y._mjs.expiration = Date.now() + 1e3 * e.attributes.cachingPolicy.maxAge, this._removeOnExpiration && this._expiryRecords.add(y)), this._populateDataAttributes(e, y), "object" == typeof e.relationships && Object.keys(e.relationships).forEach(h => {
      let m = e.relationships[h];
      m && "data" in m && (m = this.populateDataRecords(m, n, {mapping: p, parents: [{relationshipName: h, parentType: y.type, parentId: y.id}]}), y.setProperty(h, m, "relationships", d));
    }), "object" == typeof e.views && Object.keys(e.views).forEach(d => {
      const h = e.views[d];
      if (h.attributes || h.data) {
        const e = new DataRecord("view", d);
        if (this._populateDataAttributes(h, e), h.data) {
          const d = this.populateDataRecords(h, n, p);
          e.setProperty("data", d, "relationships");
        }
        y.setProperty(d, e, "views");
      }
    }), y;
  }
  query(e, n) {
    this._checkForExpiredRecords();
    let includeRecord = e => false;
    return "string" == typeof e && n ? includeRecord = d => (null == d ? void 0 : d[e]) === n : "function" == typeof e ? includeRecord = n => {
      try {
        return e(n);
      } catch (Mr) {
        return false;
      }
    } : "object" == typeof e && (includeRecord = n => {
      const d = Object.keys(e);
      let h = 0;
      return d.forEach(d => {
        (null == n ? void 0 : n[d]) === e[d] && h++;
      }), d.length === h;
    }), Object.values(this._records).reduce((e, n) => (Object.values(n).forEach(n => {
      includeRecord(n) && e.push(n);
    }), e), []);
  }
  remove(e, n) {
    setTimeout(this._checkForExpiredRecords.bind(this), 0);
    if (!Object.prototype.hasOwnProperty.call(Object(this._records), e)) return;
    const d = this.peek(e, n);
    d && (this.dispatchEvent(ar.dataRecordWillDelete, [e, n]), d._mjs.parents && d._mjs.parents.length > 0 && d._mjs.parents.forEach(({relationshipName: e, parentType: n, parentId: h}) => {
      this.peek(n, h).removeRelative(e, d.id);
    }), delete this._records[e][n], this.dispatchEvent(ar.dataRecordDidDelete, [e, n]));
  }
  save(e, n = {}) {
    return setTimeout(this._checkForExpiredRecords.bind(this), 0), this.populateDataRecords(e, this._records, n);
  }
  _populateDataAttributes(e, n) {
    "object" == typeof e.attributes && (this.dispatchEvent(ar.dataRecordWillPopulate, [n.type, n.id]), Object.keys(e.attributes).forEach(d => {
      n.setProperty(d, e.attributes[d], "attributes");
    }), this.dispatchEvent(ar.dataRecordDidPopulate, [n.type, n.id]));
  }
  _materializeRecord(e, n) {
    const {type: d, id: h} = n, p = _objectWithoutProperties$4(n, ["type", "id"]);
    return e[d] = e[d] || {}, e[d][h] ? e[d][h].setParent(p.parents || []) : e[d][h] = new DataRecord(d, h, p), this.dispatchEvent(ar.dataRecordDidMaterialize, [d, h]), e[d][h];
  }
  _checkForExpiredRecords() {
    const e = [];
    this._expiryRecords.forEach(n => {
      Date.now() > n._mjs.expiration && (e.push([n.type, n.id]), this._expiryRecords.delete(n));
    }), e.forEach(e => {
      this.remove(...e);
    });
  }
  constructor(e = {}) {
    super([ar.dataRecordDidDelete, ar.dataRecordWillDelete, ar.dataRecordDidMaterialize, ar.dataRecordWillPopulate, ar.dataRecordDidPopulate]), this._removeOnExpiration = false, this._shouldDisableRecordReuse = true, this._records = {}, this._expiryRecords = new Set, this._removeOnExpiration = !!e.removeOnExpiration, this._mapping = e.mapping, this._shouldDisableRecordReuse = !!e.shouldDisableRecordReuse, this.filter = e.filter;
  }
}
