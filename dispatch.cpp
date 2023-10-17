#include "dispatch.h"

Dispatch::Dispatch()
{

}
class Dispatch {
  get source() {
    return this._source;
  }
  set source (e) {
    if (!e && this._source) return this._source.removeEventListener("message", this.handle), void (this._source = void 0);
    e.addEventListener("message", this.handle), this._source = e;
  }
  apply(e, n) {
    if (!this.destination) throw new Error("No destination");
    const d = this._sequence++, h = new Promise((e, n) => {
      this._registry[d] = {resolve: e, reject: n};
    });
    return this.send(this.destination, {jsonrpc: "2.0", id: d, method: e, params: n}), h;
  }
  call(e, ...n) {
    return this.apply(e, n);
  }
  handleRequest(e) {
    var n, d = this;
    return (n = function* () {
      const n = {jsonrpc: "2.0", id: e.id}, h = d.methods[e.method];
      if (!h) return Object.assign(n, {error: {code: Oe.MethodNotFound, message: "Method not found"}});
      try {
        const d = yield h.apply(void 0, ensureArray(e.params));
        return Object.assign(n, {result: d});
      } catch (z) {
        return Object.assign(n, {error: {code: z.code || Oe.InternalError, message: z.message}});
      }
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$17(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$17(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  handleResponse(e) {
    const n = this._registry[e.id];
    delete this._registry[e.id], n && (e.error ? n.reject(Object.assign(Error(), e.error)) : n.resolve(e.result));
  }
  send(e, n) {
    e.postMessage(n, e.window === e ? this.origin : void 0);
  }
  constructor(e = {}) {
    this._registry = {}, this._sequence = 0, this.handle = e => {
      e.data && "2.0" === e.data.jsonrpc && ("*" !== this.origin && this.origin !== e.origin || (e.data.method && this.destination ? this.handleRequest(e.data).then(e => {
        this.send(this.destination, e);
      }) : (Object.prototype.hasOwnProperty.call(Object(e.data), "result") || e.data.error) && this.handleResponse(e.data)));
    }, this.destination = e.destination, this.methods = e.methods || {}, this.origin = e.origin || "*", e.source && (this.source = e.source);
  }
}
