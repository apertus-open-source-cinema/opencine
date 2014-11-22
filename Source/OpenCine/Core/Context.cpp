#include "Context.h"

#include <LibRawDataProvider.h>

OCContext::OCContext() :
_session(nullptr)
{
  _dataProvider = new LibRawDataProvider();
}
