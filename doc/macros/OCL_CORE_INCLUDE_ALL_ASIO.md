# OCL_CORE_INCLUDE_ALL_ASIO: MACRO

This macro includes all of the ASIO headers in OCL.Core, it is disabled by default, thus only the following headers are included:

```cpp
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
```

