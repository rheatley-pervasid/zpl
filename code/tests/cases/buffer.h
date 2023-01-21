MODULE(buffer, {
    IT("generally works", {
        zpl_buffer_make(int, b1, zpl_heap(), 4);
        zpl_buffer_free(b1);

        EQUALS(zpl_buffer_init(b1, zpl_heap(), 5), true);
        EQUALS(zpl_buffer_count(b1), 0);
        zpl_buffer_append(b1, 1);
        EQUALS(zpl_buffer_count(b1), 1);
        zpl_buffer_append(b1, 2);
        EQUALS(zpl_buffer_count(b1), 2);

        int to_add[3] = {3, 4, 5};
        zpl_buffer_appendv(b1, to_add, 3);
        EQUALS(zpl_buffer_count(b1), 5);

        {
            int *b2;
            EQUALS(zpl_buffer_copy_init(b2, b1), true);
            EQUALS(zpl_buffer_count(b2), 5);
            zpl_buffer_pop(b2);
            EQUALS(zpl_buffer_count(b2), 4);
            zpl_buffer_clear(b2);
            EQUALS(zpl_buffer_count(b2), 0);
            zpl_buffer_free(b2);
        }

        EQUALS(zpl_buffer_count(b1), 5);
        zpl_buffer_pop(b1);
        zpl_buffer_pop(b1);
        zpl_buffer_pop(b1);
        EQUALS(zpl_buffer_count(b1), 2);
        zpl_buffer_free(b1);
    });
});
