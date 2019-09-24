# Container

列出幾個常用的容器

### vector 
![](/img/vector.png "vector")

可以看成是動態陣列
- 支援隨機存取，可用[ ]取值
- 可在任何位置插入/刪除元素，但在末(尾)端效率較佳
- 宣告時可以不用指定大小，vector 會自動分配。插入超過容量，也會重新分配更大的記憶體空間，而記憶體重新分配費時，盡量減少此情況發生
- 一旦記憶體重新分配，vector 元素相關的所有 reference、pointers、iterators，都會失效

### list
![](/img/list.png "list")

- 不支援隨機存取，在list中隨機尋訪任意元素是很緩慢的行為
- 任何位置上(不只兩端)執行元素的安插和移除都非常快，始終都是常數時間內完成，因為無須移動任何其他元素。
- 安插和刪除動作並不會造成指向其他元素的各個pointers、references、iterators失效。

### deque
![](/img/deque.png "deque")

容器deque和vector非常相似。它也採用dynamic array來管理元素，提供隨機存取，並有著和vector幾乎一模一樣的介面。不同的是deque的dynamic array頭尾都開放，因此能在頭尾兩端進行快速安插和刪除。

以下情形最好採用deque：
- 你需要在兩端安插和移除元素。
- 無須指涉(refer to)容器內的元素
- 要求「不再使用的元素必須釋放」(不過C++Standard對此無任何保證)。 
  
deques的各項操作只有以下兩點和vectors不同：
- deques不提供容量操作(capacity()和reserve())。
- deques直接提供函式完成頭部元素的安插和刪除(push_front()和pop_front())。


### stack
![](/img/stack.png "stack")

- 使用push()將任意數量的元素置入stack中，也可以使用pop()將元素依其插入的相反次序從容器中移除(此即所謂「後進先出」，LIFO)。

### queue
![](/img/queue.png "queue")

- 使用push()將任意數量的元素置入queue中，也可以使用pop()將元素依其插入次序從容器中移除(此即所謂「先進先出」，FIFO)。