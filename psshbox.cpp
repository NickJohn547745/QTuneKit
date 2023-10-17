#include "psshbox.h"

PsshBox::PsshBox()
{

}
class PsshBox extends BaseMp4Box {
  get systemId() {
    const {data: e, start: n} = this, d = n + 12;
    return e.slice(d, d + 16);
  }
  get dataSize() {
    return this.view.getUint32(28);
  }
  get psshData() {
    const {data: e, start: n, dataSize: d} = this, h = n + 32;
    return e.slice(h, h + d);
  }
  get keyBytes() {
    const {psshData: e} = this;
    return e.slice(2, 18);
  }
  get isWidevine() {
    return arrayEquals(this.systemId, Ka);
  }
  constructor(e, n, d) {
    super("pssh", e, n, d), this.view = new DataView(e.buffer, n);
  }
}
