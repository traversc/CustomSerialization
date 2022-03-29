This package contains an S4 class with a reference object as data, an external pointer of a std::map. 

By utilizing ALTREP serialization methods, we are able to serialize and unserialize the external pointer with saveRDS/readRDS and no extra effort by the user. 

Demo:

```
library(CustomSerialization)

obj <- make_string_map(letters, LETTERS)
print(obj)
# a       A
# b       B
# c       C
# ...
# z       Z

add(obj, list(1:10, 10:1))
print(obj)
# 1       10
# 10      1
# 2       9
# ...
# z       Z

save_file <- tempfile()
saveRDS(obj, file = save_file)

obj2 <- readRDS(save_file)
print(obj2)
# 1       10
# 10      1
# 2       9
# ...
# z       Z
```
