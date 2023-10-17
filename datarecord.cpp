#include "datarecord.h"

DataRecord::DataRecord(QString p_type, QString p_id, JObject d)
{
    type = p_type;
    id = p_id;
    _meta = {};

    _mjs = JObject();
    _mjs["attributes"] = QVariant(QStringList());
    _mjs["relationships"] = QVariant(QStringList());
    _mjs["views"] = QVariant(QStringList());

    QList<JObject> jObjs = QList<JObject>();
    jObjs << _mjs;
    jObjs << d;
    _mjs = mergeObjects(jObjs);
}

bool DataRecord::hasProperties(JObject obj) {
    bool result = true;
    if (obj != NULL) {
        if (obj.contains("attributes") || obj.contains("relationships") || obj.contains("views")) {
            result = hasAttributes(obj["attributes"].toStringList()) &&
                     hasRelationships(obj["relationships"].toStringList()) &&
                     hasViews(obj["views"].toStringList());
        } else {
            result = hasAttributes(QStringList()) || hasRelationships(QStringList()) || hasViews(QStringList());
        }
    }
    return result;
}

bool DataRecord::hasAttributes(QStringList attrs) {
    return _hasProperties(_mjs["attributes"].toStringList(), attrs);
}

bool DataRecord::hasRelationships(QStringList rels) {
    return _hasProperties(_mjs["relationships"].toStringList(), rels);
}

bool DataRecord::hasViews(QStringList views) {
    return _hasProperties(_mjs["views"].toStringList(), views);
}

auto DataRecord::meta(auto e) {
    return e ? _meta[e] : _meta;
}

auto DataRecord::serialize(e = true, n = {}, d = {}) {
    const h = {id: this.id, type: this.type};
    return n[`${this.type}-${this.id}`] && !d.allowFullDuplicateSerializations ? h : (n[`${this.type}-${this.id}`] = true, this.hasAttributes() && (h.attributes = this._mjs.attributes.reduce((e, n) => (e[n] = this[n], e), {})), this._mjs.relationships.length > 0 && (h.relationships = this._serializeRelatedData(this._mjs.relationships, n, d)), this._mjs.views.length > 0 && (h.views = this._serializeRelatedData(this._mjs.views, n, d)), e ? {data: h} : h);
}

auto DataRecord::setProperty(e, n, d = "attributes", h = {}) {
    Object.prototype.hasOwnProperty.call(Object(this), e) || (this._mjs[d] || (this._mjs[d] = []), this._mjs[d].push(e));
    const setDescriptor = e => ({value: e, writable: true, configurable: true, enumerable: true});
    this[e] && n && "object" == typeof this[e] && "object" == typeof n ? "attributes" === d ? Object.defineProperty(this, e, setDescriptor(deepmerge(this[e], n, {arrayMerge: function (e, n, d) {
      return n;
    }, isMergeableObject: isMergeableObject}))) : "relationships" === d && Array.isArray(this[e]) && h.extendRelationships ? Object.defineProperty(this, e, setDescriptor(deepmerge(this[e], n, {isMergeableObject: isMergeableObject}))) : Object.defineProperty(this, e, setDescriptor(n)) : Object.defineProperty(this, e, setDescriptor(n));
}

void DataRecord::removeRelative(e, n) {
    this[e] &&
            (Array.isArray(this[e]) ? this[e] = this[e].filter(e => e.id !== n) : delete this[e]);
}

void DataRecord::setParent(QString newPar) {
    QStringList parents = _mjs["parents"].toStringList();

    parents.append(newPar);
    _mjs["parents"] = QVariant(parents);
}

bool DataRecord::_hasProperties(QStringList e, QStringList n) {
    bool result = false;
    if (e.isEmpty()) {
        bool temp = true;
        if (!n.isEmpty()) {
            foreach (QString s, n) {
                temp &= e.contains(s);
            }
        } else {
            temp = e.count() > 0;
        }
        result = temp;
    }
    return result;
}

_serializeRelatedData(e, n = {}, d = {}) {
    return e.reduce((e, h) => {
      if (d.excludeRelationships && d.excludeRelationships.has(h)) return e;
      if (d.includeRelationships && !d.includeRelationships.has(h)) return e;
      const p = this[h];
      return Array.isArray(p) ? e[h] = {data: p.map(e => "function" == typeof e.serialize ? e.serialize(false, n, d) : e)} : e[h] = p && "function" == typeof p.serialize ? p.serialize(false, n, d) : p, e;
    }, {});
  }

}
