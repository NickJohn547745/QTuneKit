#include "playactivitybatchablesender.h"

PlayActivityBatchableSender::PlayActivityBatchableSender(e, n)
{
    this.sender = e;
    this.jar = n;
    this.mode = Jn;
}

void PlayActivityBatchableSender::flush() {
    var e = this;
    return _asyncToGenerator$Z(function* () {
      const n = read(e.jar, "amupaee");
      if (void 0 !== n && 0 !== n.length) try {
        yield e.sender.send(n), empty(e.jar, "amupaee");
      } catch ({message: d}) {
        throw new Error("flush: " + d);
      }
    })();
  }

void PlayActivityBatchableSender::send(n) {
    var d = this;
    return _asyncToGenerator$Z(function* () {
      if (d.mode === Jn && (Array.isArray(n) || n["end-reason-type"] !== e.PlayActivityEndReasonType.EXITED_APPLICATION)) return d.sender.send(n);
      var h, p, y, m, g, b;
      h = d.jar, y = n, m = "/", write(h, p = "amupaee", [...read(h, p), y], m, g, b);
    })();
  }
}
