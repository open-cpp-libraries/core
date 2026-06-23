# IOAble (Container must be IO oriented)

## Abstract:

- Introduced: OCL v1.7
- Purpose: Gives a container the methods to communicate with injectors such as transaction<IOAble>, or std::ostream<IOAble>.

## Example:

```cpp
   struct IORound final {
    long operator>>(float); 
    float operator<<(long);
    long operator*(); // latest IO value (copy-constructable). 
   };
```

## Properties:



## References:

- https://en.cppreference.com/w/cpp/named_req/CopyConstructible.html
