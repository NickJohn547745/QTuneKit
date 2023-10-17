#include "statelessplayactivity.h"

StatelessPlayActivity::StatelessPlayActivity()
{

}
class StatelessPlayActivity extends PlayActivityBase {
  build(e, n) {
    return buildPlayActivityData$1(this, e, n, "JSCLIENT" !== this.clientId);
  }
  constructor(e, n, d, h) {
    super(e, n, d, h);
  }
}
