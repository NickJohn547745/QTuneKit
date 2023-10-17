#include "logger.h"

Logger::Logger()
{

}

  get parent() {
    return this._parent;
  }
  get children() {
    return Array.from(this._children.values());
  }
  get namespace() {
    return void 0 === this._parent ? this.name : this._parent.namespace + "/" + this.name;
  }
  get enabled() {
    return this.level !== A.NONE;
  }
  get level() {
    var e, n, d;
    return null !== (d = null !== (n = this._level) && void 0 !== n ? n : null === (e = this.parent) || void 0 === e ? void 0 : e.level) && void 0 !== d ? d : C;
  }
  get levelName() {
    var e;
    return null !== (e = getLoggingLevelName(this.level)) && void 0 !== e ? e : "UNKNOWN";
  }
  get levelPolicy() {
    var e, n, d;
    return null !== (d = null !== (n = this._levelPolicy) && void 0 !== n ? n : null === (e = this.parent) || void 0 === e ? void 0 : e.levelPolicy) && void 0 !== d ? d : DEFAULT_POLICY;
  }
  get handlers() {
    var e, n, d;
    return null !== (d = null !== (n = this._handlers) && void 0 !== n ? n : null === (e = this.parent) || void 0 === e ? void 0 : e.handlers) && void 0 !== d ? d : {};
  }
  isEnabledFor(e) {
    return this.levelPolicy(this.level, e);
  }
  setLevel(e) {
    const n = getLoggingLevel(e);
    void 0 !== n && (this._level = n);
  }
  clearLevel() {
    this._level = void 0;
  }
  setLevelPolicy(e) {
    this._levelPolicy = e;
  }
  clearLevelPolicy() {
    this._levelPolicy = void 0;
  }
  addHandler(e, n) {
    this._handlers || (this._handlers = {}), this._handlers[e] = n;
  }
  hasHandler(e) {
    var n;
    return void 0 !== (null === (n = this._handlers) || void 0 === n ? void 0 : n[e]);
  }
  removeHandler(e) {
    void 0 !== this._handlers && (delete this._handlers[e], 0 === Object.keys(this._handlers).length && this.clearHandlers());
  }
  clearHandlers() {
    this._handlers = void 0;
  }
  createChild(e, n) {
    const d = this._children.get(e);
    return void 0 !== d ? d : new Logger(e, _objectSpreadProps$t(_objectSpread$L({}, n), {parent: this}));
  }
  linkChild(e) {
    if (void 0 !== e.parent && e.parent !== this) throw new Error(`Logger '${e.name}' is already a child of a different parent ('${e.parent.name}')`);
    const n = this._children.get(e.name);
    if (void 0 !== n && n !== e) throw new Error(`A child with name '${e.name}' is already registered`);
    return void 0 === n && (this._children.set(e.name, e), e.linkParent(this)), e;
  }
  unlinkChild(e) {
    const n = this._children.get(e.name);
    return n === e && (this._children.delete(e.name), n.unlinkParent()), e;
  }
  getByName(e) {
    return this._children.get(e);
  }
  getByNamespace(e) {
    return function (e, n, d = "/") {
      if ("" === (n = n.trim()) || "*" === n) return e;
      const h = n.split(d);
      h[0].trim() === e.name && h.shift();
      if (0 === h.length) return e;
      let p = e;
      for (; void 0 !== p && h.length > 0;) {
        const e = h.shift();
        p = p.getByName(e.trim());
      }
      return p;
    }(this, e);
  }
  linkParent(e) {
    return this.parent !== e && (this.unlinkParent(), this._parent = e, e.linkChild(this)), this;
  }
  unlinkParent() {
    return void 0 !== this._parent && (this._parent.unlinkChild(this), this._parent = void 0), this;
  }
  log(e, n, ...d) {
    const h = getLoggingLevel(e);
    void 0 !== h && this.logRecord({time: Date.now(), namespace: this.namespace, level: h, message: n, args: d});
  }
  logRecord(e) {
    if (!this.levelPolicy(this.level, e.level)) return;
    const n = _objectSpread$L({namespace: this.namespace}, e);
    for (const d of Object.values(this.handlers)) d.process(n);
  }
  error(e, ...n) {
    this.log(A.ERROR, e, ...n);
  }
  warning(e, ...n) {
    this.log(A.WARNING, e, ...n);
  }
  warn(e, ...n) {
    this.warning(e, ...n);
  }
  info(e, ...n) {
    this.log(A.INFO, e, ...n);
  }
  debug(e, ...n) {
    this.log(A.DEBUG, e, ...n);
  }
  trace(e, ...n) {
    this.log(A.TRACE, e, ...n);
  }
  constructor(e, n) {
    this._children = new Map, this.name = e, this._levelPolicy = null == n ? void 0 : n.levelPolicy, this._handlers = null == n ? void 0 : n.handlers, void 0 !== (null == n ? void 0 : n.parent) && this.linkParent(n.parent), void 0 !== (null == n ? void 0 : n.level) && this.setLevel(n.level);
  }
}
