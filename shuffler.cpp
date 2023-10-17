#include "shuffler.h"

Shuffler::Shuffler()
{

}
class Shuffler {
  get queue() {
    return this._queue;
  }
  set queue (e) {
    this._queue = e, this._unshuffledIDs = e.userAddedItems.map(e => e.id), this.checkAndReshuffle(false);
  }
  queueModifiedHandler(e, n) {
    if (this._isSpliceFromShuffle) return void (this._isSpliceFromShuffle = false);
    const {start: d, added: h, removed: p} = n;
    if (p.length > 0) {
      const e = p.map(e => e.id);
      this._unshuffledIDs = this._unshuffledIDs.filter(n => !e.includes(n));
    }
    h.length > 0 && this._unshuffledIDs.splice(d, 0, ...h.map(e => e.id));
  }
  set shuffle (n) {
    this.shuffleMode = n ? e.PlayerShuffleMode.songs : e.PlayerShuffleMode.off;
  }
  get shuffleMode() {
    return this.mode;
  }
  set shuffleMode (n) {
    n !== this.shuffleMode && n in e.PlayerShuffleMode && (Mt.debug(`mk: set shuffleMode from ${this.shuffleMode} to ${n}`), this.mode = n, this.mode === e.PlayerShuffleMode.songs ? this.shuffleQueue() : this.unshuffleQueue(), this.controller.nowPlayingItem && (this._queue.position = this._queue.indexForItem(this.controller.nowPlayingItem.id)), this.dispatcher.publish(ss.shuffleModeDidChange, this.shuffleMode));
  }
  checkAndReshuffle(n = false) {
    this.shuffleMode === e.PlayerShuffleMode.songs && this.shuffleQueue(n);
  }
  shuffleQueue(e = true) {
    const {userAddedItems: n} = this._queue;
    if (n.length <= 1) return n;
    const d = n.slice(0), h = this._queue.position > -1 ? d.splice(this._queue.position, 1) : [];
    let p = [];
    do {
      p = shuffleCollection(d);
    } while (d.length > 1 && arrayEquals(p, d));
    const y = [...h, ...p];
    this._isSpliceFromShuffle = true, this._queue.spliceQueueItems(0, y.length, y.map(e => new QueueItem(y, n)), e);
  }
  unshuffleQueue(e = true) {
    let n = [];
    const d = this._unshuffledIDs.reduce((e, n, d) => (e[n] = d, e), {}), h = [];
    let p = 0;
    const y = this._queue.item(this._queue.position);
    this._queue.userAddedItems.forEach(e => {
      const m = d[e.id];
      void 0 === m && h.push(e), n[m] = e, e.id === (null == y ? void 0 : y.id) && (p = m);
    }), n = n.filter(Boolean);
    const m = n.concat(h);
    this._isSpliceFromShuffle = true, this._queue.spliceQueueItems(0, m.length, m.map(e => new QueueItem(m, n)), e), this._queue.position = p;
  }
  constructor(n, {dispatcher: d}) {
    this.controller = n, this.canSetShuffleMode = true, this.mode = e.PlayerShuffleMode.off, this._unshuffledIDs = [], this._isSpliceFromShuffle = false, this.dispatcher = d, this.dispatcher.subscribe(lr.queueModified, this.queueModifiedHandler), this._queue = n.queue;
  }
}
