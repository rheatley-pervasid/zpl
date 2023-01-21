MODULE(string, {
    IT("can split two lines", {
        zpl_string to_split = zpl_string_make(zpl_heap(), "1\n2\n");
        char **lines = zpl_str_split_lines(zpl_heap(), to_split, false);
        EQUALS(zpl_array_count(lines), 2);
        STREQUALS(lines[0], "1");
        STREQUALS(lines[1], "2");
        zpl_array_free(lines);
        zpl_string_free(to_split);
    });
    IT("can split one line", {
        zpl_string to_split = zpl_string_make(zpl_heap(), "test");
        char **lines = zpl_str_split_lines(zpl_heap(), to_split, false);
        EQUALS(zpl_array_count(lines), 1);
        STREQUALS(lines[0], "test");
        zpl_array_free(lines);
        zpl_string_free(to_split);
    });
});
