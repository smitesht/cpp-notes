# unique_ptr

std::unique_ptr is a smart pointer that manages an object or an array allocated on the heap through a raw pointer.
It performs an appropriate disposal when the smart pointer goes out of scope.

- std::unique_ptr has exclusive ownership of resource.
- A non-null unique_ptr always owns what it point to
- Moving a std:: unique_ptr transfer ownership from the resource pointer to the destination pointer. The source pointer is set to null.
- Copy is not allowed as the unique_ptr always has only one owner.
- A non-null unique_ptr destroys its resource. Internally, it calls delete to the raw pointer.
- By default, resource destructor take place vvia delete, but custome deleter can also be used when need special deletion.
