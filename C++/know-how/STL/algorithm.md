#### reference
> http://c.biancheng.net/stl/  
> http://www.cplusplus.com/reference/algorithm/

## \<algorithm\>
無修改型序列操作

function|discraption
---|---
all_of  |序列(迭代器範圍)內所有元素是否符合條件, 回傳true/false
any_of  |序列內至少有一個元素符合條件, 回傳true/false
none_of |序列內沒有元素符合條件, 回傳true/false
for_each|序列內每個元素丟入函數執行運算
find    |序列內尋找單一值, 回傳找到對象的迭代器
find_if |同find, 但為回傳*讓給定條件為true*的迭代器
find_if_not|與find_if相反, 回傳*讓給定條件為false*的迭代器
find_end|序列內尋找*最後一組*與另一個迭代器相匹配的方法, 回傳最後一組相匹配項第一個元素的迭代器
find_first_of|在第一個序列內搜尋第二個序列的任何元素, 或是第一個序列元素與第二個序列元素符合條件, 回傳第一個符合的迭代器
adjacent_find|序列內搜尋連續相等的兩個元素, 回傳相等兩元素中第一個的迭代器
count|累計序列內某數的個數, 回傳個數
count_if|累計序列內符合條件的個數, 回傳個數
mismatch|判斷兩序列是否相等, 若不匹配則回傳std::pair
equal|若兩序列長度且對應元素相等, 回傳true
is_permutation|判斷序列依是否為序列二的排序, 回傳true/false
search|同find_end, 但為尋找第一組匹配項目
search_n|搜尋序列中某數連續出現n次, 回傳連續出現n次的第一個元素的迭代器

修改型序列操作

function|discraption
---|---
copy|複製序列至另一序列中
copy_n|複製序列的n個元素至另一序列中
copy_if|複製序列中符合條件的元素至另一序列中
copy_backward|複製序列至另一序列的末端(不會改變原序列順序)
move|
move_backward|
swap|
swap_ranges|
iter_swap|
transform|
replace|
replace_if|
replace_copy|
replace_copy_if|
fill|
fill_n|
generate|
generate_n|
remove|
remove_if|
remove_copy|
remove_copy_if|
unique|
unique_copy|
reverse|
reverse_copy|
rotate|
rotate_copy|
random_shuffle|
shuffle|

Partitions:

function|discraption
---|---
is_partitioned|
partition|
stable_partition|
partition_copy|
partition_point|

Sorting:

function|discraption
---|---
sort|
stable_sort|
partial_sort|
partial_sort_copy|
is_sorted|
is_sorted_until|
nth_element|

Binary search(operating on partitioned/sorted ranges):

function|discraption
---|---
lower_bound|
upper_bound|
equal_range|
binary_search|

Merge(operating on sorted ranges):

function|discraption
---|---
merge|
inplace_merge|
includes|
set_union|
set_intersection|
set_difference|
set_symmetric_difference|

Heap:

function|discraption
---|---
push_heap|
pop_heap|
make_heap|
sort_heap|
is_heap|
is_heap_until|

Min/max:

function|discraption
---|---
min|
max|
minmax|
min_element|
max_element|
minmax_element|
