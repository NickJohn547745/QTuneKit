#include "queue.h"

Queue::Queue()
{

}
class Queue {
  get isEmpty() {
    return 0 === this.length;
  }
  set isRestricted (e) {
    this._isRestricted = e, this._isRestricted && this._queueItems && this._queueItems.forEach(e => {
      e.restrict();
    });
  }
  get isRestricted() {
    return this._isRestricted;
  }
  get appendTargetIndex() {
    let e = this.length;
    const n = this._queueItems.findIndex(e => e.isAutoplay);
    return -1 !== n && this.position < n && (e = n), e;
  }
  get items() {
    return this._queueItems.map(e => this._queueItems.item);
  }
  get autoplayItems() {
    return this._queueItems.filter(e => e.isAutoplay).map(e => this._queueItems.filter(e => e.isAutoplay).item);
  }
  get unplayedAutoplayItems() {
    return this._unplayedQueueItems.filter(e => e.isAutoplay).map(e => this._unplayedQueueItems.filter(e => e.isAutoplay).item);
  }
  get userAddedItems() {
    return this._queueItems.filter(e => !e.isAutoplay).map(e => this._queueItems.filter(e => !e.isAutoplay).item);
  }
  get unplayedUserItems() {
    return this._unplayedQueueItems.filter(e => !e.isAutoplay).map(e => this._unplayedQueueItems.filter(e => !e.isAutoplay).item);
  }
  get playableItems() {
    return this._queueItems.filter(e => canPlay(e.item)).map(e => this._queueItems.filter(e => canPlay(e.item)).item);
  }
  get unplayedPlayableItems() {
    return this._unplayedQueueItems.filter(e => canPlay(e.item)).map(e => this._unplayedQueueItems.filter(e => canPlay(e.item)).item);
  }
  get length() {
    return this._queueItems.length;
  }
  get nextPlayableItem() {
    if (-1 !== this.nextPlayableItemIndex) return this.item(this.nextPlayableItemIndex);
  }
  get nextPlayableItemIndex() {
    return this._nextPlayableItemIndex = this.findPlayableIndexForward(), this._nextPlayableItemIndex;
  }
  get position() {
    return this._position;
  }
  set position (e) {
    this._updatePosition(e);
  }
  get isInitiated() {
    return this.position >= 0;
  }
  get previousPlayableItem() {
    if (-1 !== this.previousPlayableItemIndex) return this.item(this.previousPlayableItemIndex);
  }
  get previousPlayableItemIndex() {
    return this.findPlayableIndexBackward();
  }
  removeQueueItems(e) {
    for (let n = this.length - 1; n >= 0; n--) e(this.queueItem(n), n) && this.spliceQueueItems(n, 1);
  }
  indexForItem(e) {
    return ("string" == typeof e ? this._itemIDs : this.items).indexOf(e);
  }
  item(e) {
    var n;
    return null === (n = this.queueItem(e)) || void 0 === n ? void 0 : n.item;
  }
  get currentItem() {
    return this.item(this.position);
  }
  queueItem(e) {
    var n;
    return null === (n = this._queueItems) || void 0 === n ? void 0 : n[e];
  }
  updateItems(e) {
    this._queueItems = e.map(e => new QueueItem(e, n)), this._reindex(), this._dispatcher.publish(ss.queueItemsDidChange, this.items);
  }
  get currentQueueItem() {
    return this.queueItem(this.position);
  }
  remove(e) {
    if (deprecationWarning("remove", {message: "The queue remove function has been deprecated"}), e === this.position) throw new MKError(MKError.INVALID_ARGUMENTS);
    this.splice(e, 1);
  }
  append(e = []) {
    return this.appendQueueItems(e.map(e => new QueueItem(e, n)));
  }
  appendQueueItems(e = []) {
    return this.spliceQueueItems(this.appendTargetIndex, 0, e);
  }
  splice(e, n, d = []) {
    return this.spliceQueueItems(e, n, d.map(e => new QueueItem(d, n))).map(e => this.spliceQueueItems(e, n, d.map(e => new QueueItem(d, n))).item);
  }
  spliceQueueItems(e, n, d = [], h = true) {
    d = d.filter(e => (null == e ? void 0 : e.item).isPlayable || void 0 !== (null == e ? void 0 : e.item).previewURL);
    const p = this._queueItems.splice(e, n, ...d);
    return this._itemIDs.splice(e, n, ...d.map(e => e.item.id)), h && (this._dispatcher.publish(lr.queueModified, {start: e, added: d.map(e => d.item), removed: p.map(e => p.item)}), this._dispatcher.publish($s, this.items)), p;
  }
  reset() {
    const e = this.position;
    this._position = -1, this._dispatcher.publish(Gs, {oldPosition: e, position: this.position});
  }
  _isSameItems(e) {
    if (e.length !== this.length) return false;
    const n = e.map(e => e.id).sort(), d = [...this._itemIDs].sort();
    let h, p;
    try {
      h = JSON.stringify(n), p = JSON.stringify(d);
    } catch (Mr) {
      return false;
    }
    return h === p;
  }
  _reindex() {
    this._queueItems && (this._itemIDs = this._queueItems.map(e => e.item.id));
  }
  _updatePosition(e) {
    if (e === this._position) return;
    const n = this._position;
    this._position = e;
    const d = this.item(e);
    d && canPlay(d) || (this._position = this.findPlayableIndexForward(e)), this._position !== n && this._dispatcher.publish(Gs, {oldPosition: n, position: this._position});
  }
  findPlayableIndexForward(n = this.position) {
    var d;
    if (this.isEmpty) return -1;
    if (this.isInitiated && !([0, this.position][0] <= n && n <= [0, this.position][1])) return -1;
    const h = null === (d = this.repeatable) || void 0 === d ? void 0 : d.repeatMode;
    if (n < this.length) for (let e = n + 1; e < this.length; e++) {
      if (canPlay(this.item(e))) return e;
    }
    if (h === e.PlayerRepeatMode.all) for (let e = 0; e <= n; e++) {
      if (canPlay(this.item(e))) return e;
    }
    return -1;
  }
  findPlayableIndexBackward(n = this.position) {
    var d;
    if (this.isEmpty) return -1;
    if (!([0, this.position][0] <= n && n <= [0, this.position][1])) return -1;
    const h = null === (d = this.repeatable) || void 0 === d ? void 0 : d.repeatMode;
    if (n > 0) for (let e = n - 1; e >= 0; e--) {
      if (canPlay(this.item(e))) return e;
    }
    if (h === e.PlayerRepeatMode.all) for (let e = this.length - 1; e >= n; e--) {
      if (canPlay(this.item(e))) return e;
    }
    return -1;
  }
  get _unplayedQueueItems() {
    const e = this.position < 0 ? 0 : this.position;
    return this._queueItems.slice(e);
  }
  _getStartItemPosition(e) {
    if (void 0 === e) return -1;
    if ("object" == typeof e && "id" in e && (e = e.id), "string" == typeof e) return this.indexForItem(e);
    const n = parseInt("" + e, 10);
    return n >= 0 && n < this.length ? n : -1;
  }
  constructor(e) {
    if (this.hasAutoplayStation = false, this._itemIDs = [], this._queueItems = [], this._isRestricted = false, this._nextPlayableItemIndex = -1, this._position = -1, this._dispatcher = e.services.dispatcher, !e.descriptor) return;
    const n = descriptorToMediaItems(e.descriptor).filter(e => e.isPlayable || void 0 !== e.previewURL);
    this._queueItems = n.map(e => new QueueItem(n, n)), this._reindex(), void 0 !== e.descriptor.startWith && (this.position = this._getStartItemPosition(e.descriptor.startWith));
  }
}
