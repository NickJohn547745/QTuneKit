#include "parsingerror.h"

ParsingError::ParsingError()
{

}
class ParsingError extends Error {
  constructor(e, n) {
    super(), this.name = "ParsingError", this.code = "number" == typeof e ? e : e.code, n ? this.message = n : e instanceof ParsingError && (this.message = e.message);
  }
}
