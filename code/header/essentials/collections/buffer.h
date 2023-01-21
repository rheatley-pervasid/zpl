// file: header/essentials/collections/buffer.h

////////////////////////////////////////////////////////////////
//
// Fixed Capacity Buffer (POD Types)
//
//
// zpl_buffer(Type) works like zpl_string or zpl_array where the actual type is just a pointer to the first
// element.
//
// Available Procedures for zpl_buffer(Type)
// zpl_buffer_init
// zpl_buffer_free
// zpl_buffer_append
// zpl_buffer_appendv
// zpl_buffer_pop
// zpl_buffer_clear


ZPL_BEGIN_C_DECLS

typedef struct zpl_buffer_header {
    zpl_allocator backing;
    zpl_isize elem_size;
    zpl_isize count;
    zpl_isize capacity;
} zpl_buffer_header;

#define zpl_buffer(Type) Type *

#define zpl_buffer_make(Type, Name, allocator, cap) Type *Name; zpl_buffer_init(Name, allocator, cap)

#define ZPL_BUFFER_HEADER(x)   (cast(zpl_buffer_header *)(x) - 1)
#define zpl_buffer_allocator(x) (ZPL_BUFFER_HEADER(x)->backing)
#define zpl_buffer_elem_size(x) (ZPL_BUFFER_HEADER(x)->elem_size)
#define zpl_buffer_count(x)    (ZPL_BUFFER_HEADER(x)->count)
#define zpl_buffer_capacity(x) (ZPL_BUFFER_HEADER(x)->capacity)
#define zpl_buffer_end(x) (x + (zpl_buffer_count(x) - 1))

ZPL_IMPL_INLINE zpl_b8 zpl__buffer_init(void **nx, zpl_allocator allocator, zpl_isize elem_size, zpl_isize cap) {
    zpl_buffer_header *zpl__bh =
    cast(zpl_buffer_header *) zpl_alloc(allocator, sizeof(zpl_buffer_header) + cap * elem_size);
    if (!zpl__bh) return false;
    zpl__bh->backing = allocator;
    zpl__bh->elem_size = elem_size;
    zpl__bh->count = 0;
    zpl__bh->capacity = cap;
    *nx = cast(void *)(zpl__bh + 1);
    return true;
}

#define zpl_buffer_init(x, allocator, cap)  zpl__buffer_init(cast(void **) & (x), allocator, zpl_size_of(*(x)), cap)

#define zpl_buffer_free(x) (zpl_free(ZPL_BUFFER_HEADER(x)->backing, ZPL_BUFFER_HEADER(x)))

#define zpl_buffer_append(x, item)                                                                                     \
do {                                                                                                               \
    ZPL_ASSERT(zpl_buffer_count(x) < zpl_buffer_capacity(x));                                                      \
    (x)[zpl_buffer_count(x)++] = (item);                                                                           \
} while (0)                                                                                                        \

#define zpl_buffer_appendv(x, items, item_count)                                                                       \
do {                                                                                                               \
    ZPL_ASSERT(zpl_size_of(*(items)) == zpl_size_of(*(x)));                                                        \
    ZPL_ASSERT(zpl_buffer_count(x) + item_count <= zpl_buffer_capacity(x));                                        \
    zpl_memcopy(&(x)[zpl_buffer_count(x)], (items), zpl_size_of(*(x)) * (item_count));                             \
    zpl_buffer_count(x) += (item_count);                                                                           \
} while (0)

ZPL_IMPL_INLINE zpl_b8 zpl__buffer_copy_init(void **y, void **x) {
    if (!zpl__buffer_init(y, zpl_buffer_allocator(*x), zpl_buffer_elem_size(*x), zpl_buffer_capacity(*x)))
        return false;
    zpl_memcopy(*y, *x, zpl_buffer_capacity(*x) * zpl_buffer_elem_size(*x));
    zpl_buffer_count(*y) = zpl_buffer_count(*x);
    return true;
}

#define zpl_buffer_copy_init(y, x) zpl__buffer_copy_init(cast(void **) & (y), cast(void **) & (x))

#define zpl_buffer_pop(x)                                                                                              \
do {                                                                                                               \
    ZPL_ASSERT(zpl_buffer_count(x) > 0);                                                                           \
    zpl_buffer_count(x)--;                                                                                         \
} while (0)

#define zpl_buffer_clear(x)                                                                                            \
do { zpl_buffer_count(x) = 0; } while (0)

ZPL_END_C_DECLS
