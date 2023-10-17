#include "windowhandlers.h"

WindowHandlers::WindowHandlers()
{

}
class WindowHandlers {
  activate(e = self, n = self.document) {
    n.addEventListener(si, this.visibilityChanged), e.addEventListener("storage", this.storage, false), e.addEventListener(ci, this.windowUnloaded);
  }
  deactivate() {
    document.removeEventListener(si, this.visibilityChanged), window.removeEventListener("storage", this.storage), window.addEventListener(ci, this.windowUnloaded);
  }
  stopListeningToVisibilityChanges(e) {
    var n, d = this;
    return (n = function* () {
      d.dispatchVisibilityChanges = false;
      const n = yield e();
      return d.dispatchVisibilityChanges = true, n;
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$T(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$T(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  dispatch(e, n = {}) {
    this.player.dispatch(e, n);
  }
  storage({key: e, newValue: n}) {
    e === Vt && this.player.tsidChanged(n);
  }
  visibilityChanged(e) {
    const n = e.target[oi];
    Ct.info("dc visibilityState", n, e, ri()), this.browser.isiOS && this.dispatchVisibilityChanges && ("hidden" === n ? this.dispatch(lr.playerExit, {item: this.player.nowPlayingItem, position: this.player.currentPlaybackTime}) : "visible" === n && this.dispatch(lr.playerActivate));
  }
  windowUnloaded() {
    this.player.isPlaying && this.dispatch(lr.playerExit, {item: this.player.nowPlayingItem, position: this.player.currentPlaybackTime});
  }
  constructor(e, n = Bt) {
    this.dispatchVisibilityChanges = true, this.player = e, this.browser = n;
  }
}
