#include "timedmetadatamanager.h"

TimedMetadataManager::TimedMetadataManager()
{

}
class TimedMetadataManager {
  processEmsgs(e) {
    const n = findEmsgs(e);
    n.length && (this._currentEmsgInterval || (this._currentEmsgInterval = setInterval(this._getCurrentEmsg, 1e3)), n.forEach(e => {
      const n = new Emsg(e);
      this._emsgLookup[n.elementPresentationTime] = n;
    }));
  }
  stop() {
    const {_currentEmsgInterval: e} = this;
    e && clearInterval(e);
  }
  _getCurrentEmsg() {
    const {_currentTime: e, _emsgLookup: n} = this, d = Math.round(e()), h = [], p = Object.keys(n);
    for (let m = 0; m < p.length; m++) {
      const e = parseInt(p[m], 10);
      if (!(e < d)) break;
      h.push(e);
    }
    const y = h.pop();
    if (y) {
      const e = n[y];
      if (!e) return;
      const {_currentEmsg: d, _onDidChange: h} = this, p = null == d ? void 0 : d.payload, m = e.payload;
      p && arrayEquals(p, m) || (this._currentEmsg = e, h(e)), this._cleanupEmsgs(y);
    }
  }
  _cleanupEmsgs(e) {
    const {_emsgLookup: n} = this;
    Object.keys(n).forEach(d => {
      parseInt(d, 10) < e && delete n[d];
    });
  }
  constructor(e, n) {
    this._currentTime = e, this._onDidChange = n, this._emsgLookup = {}, this._getCurrentEmsg = this._getCurrentEmsg.bind(this);
  }
}
