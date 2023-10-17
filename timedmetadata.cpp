#include "timedmetadata.h"

TimedMetadata::TimedMetadata()
{

}
class TimedMetadata {
  resolveAdamIdFromStorefront(e) {
    const n = this.storefrontToIds[e];
    this._adamId = n;
  }
  get adamId() {
    return this._adamId;
  }
  equals(e) {
    if (!Ya.every(n => this[n] === e[n])) return false;
    const {links: n} = this, d = e.links;
    if (n.length !== d.length) return false;
    for (let h = 0; h < n.length; h++) {
      const e = n[h].description === d[h].description, p = n[h].url === d[h].url;
      if (!e || !p) return false;
    }
    return true;
  }
  constructor(e) {
    this.links = [], this.storefrontToIds = {}, e.forEach(e => {
      const {key: n} = e, d = qa[n];
      var h;
      if (d) this[d] = null === (h = e.text) || void 0 === h ? void 0 : h.replace(/\0/g, ""); else if ("WXXX" === e.key) {
        if (e.description) {
          const [n, d] = e.description.split("");
          this.links.push({description: n, url: d});
        }
      } else if ("PRIV" === e.key) {
        var p;
        const n = null === (p = e.info) || void 0 === p ? void 0 : p.split("");
        if (n && n.length && n[0].startsWith("com.apple.radio.adamid")) {
          n[1].split(",").forEach(e => {
            const [n, d] = e.split(":");
            n && d && "0" !== d && !Object.prototype.hasOwnProperty.call(Object(this.storefrontToIds), n) && (this.storefrontToIds[n] = d);
          });
        }
      }
    });
  }
}
