# map的find与count函数

来源：https://blog.csdn.net/lemn_de/article/details/119325232

map和set两种容器的底层结构都是红黑树，所以容器中不会出现相同的元素，因此count()的结果只能为0和1，可以以此来判断键值元素是否存在(当然也可以使用find()方法判断键值是否存在)。

拿map<key,value>举例:

- find()方法返回值是一个迭代器，成功返回迭代器指向要查找的元素，失败返回的迭代器指向end。
- count()方法返回值是一个整数，1表示有这个元素，0表示没有这个元素。