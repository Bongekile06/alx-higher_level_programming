#include <python3.8/Python.h>
#include <stdio.h>

void print_hexn(const char *str, int n)
{
    int i = 0;

    for (; i < n - 1; ++i)
        printf("%02x ", (unsigned char)str[i]);

    printf("%02x", str[i]);
}

void print_python_bytes(PyObject *p)
{
    PyBytesObject *clone = (PyBytesObject *)p;
    int calc_bytes, clone_size = 0;

    printf("[.] bytes object info\n");
    if (PyBytes_Check(clone))
    {
        clone_size = PyBytes_Size(p);
        calc_bytes = clone_size + 1;

        if (calc_bytes >= 10)
            calc_bytes = 10;

        printf("  size: %d\n", clone_size);
        printf("  trying string: %s\n", clone->ob_sval);
        printf("  first %d bytes: ", calc_bytes);
        print_hexn(clone->ob_sval, calc_bytes);
        printf("\n");
    }
    else
    {
        printf("  [ERROR] Invalid Bytes Object\n");
    }
}

void print_python_list(PyObject *p)
{
    int i = 0, list_len = 0;
    PyObject *item;
    PyListObject *clone = (PyListObject *)p;

    printf("[*] Python list info\n");
    list_len = PyList_GET_SIZE(p);
    printf("[*] Size of the Python List = %d\n", list_len);
    printf("[*] Allocated = %d\n", (int)clone->allocated);

    for (; i < list_len; ++i)
    {
        item = PyList_GET_ITEM(p, i);
        printf("Element %d: %s\n", i, item->ob_type->tp_name);

        if (PyBytes_Check(item))
            print_python_bytes(item);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <python_script.py>\n", argv[0]);
        return 1;
    }

    Py_Initialize();

    FILE *script_file = fopen(argv[1], "r");
    if (script_file == NULL)
    {
        fprintf(stderr, "Error: Unable to open the Python script.\n");
        return 1;
    }

    PyRun_SimpleFile(script_file, argv[1]);

    Py_Finalize();

    return 0;
}
