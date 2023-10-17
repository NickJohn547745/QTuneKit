#include "mediaapiv3.h"

MediaAPIV3::MediaAPIV3()
{

}
class MediaAPIV3 {
  configure(e, n, d = Js.Merge) {
    this.storefrontId = n.storefrontId;
    const h = function (e) {
      let n = {};
      e.url && (n.url = e.url);
      e.storefrontId && (n.defaultUrlParameters = {storefrontId: e.storefrontId});
      e.mediaUserToken && (n.defaultOptions = {fetchOptions: {headers: {"Media-User-Token": e.mediaUserToken}}});
      e.developerToken && (n = deepmerge(n, {defaultOptions: {fetchOptions: {headers: {Authorization: "Bearer " + e.developerToken}}}}));
      e.options && (n = deepmerge(n, e.options));
      return n;
    }(n);
    if (this[e]) this[e].session.reconfigure(h, d); else {
      var p;
      const n = new APISession(h), d = n.request.bind(n);
      d.session = n;
      const y = "undefined" != typeof process && "test" === (null === (p = process.env) || void 0 === p ? void 0 : p.NODE_ENV);
      Object.defineProperty(this, e, {value: d, writable: y, enumerable: true});
    }
  }
  constructor(e) {
    const {realmConfig: n} = e, d = _objectWithoutProperties(e, ["realmConfig"]);
    for (const h in Zs) {
      let e = deepmerge(Zs[h], d);
      const p = null == n ? void 0 : n[h];
      p && (e = deepmerge(e, p)), this.configure(h, e);
    }
  }
}
