#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* The project uses header-inclusion pattern; include headers to pull in .c code */
#include "opcodes_prefix.h"
#include "instrutions_format.h"
#include "stringx.h"

/* opcodes_prefix.c is NOT auto-included from its header, so include explicitly */
#include "opcodes_prefix.c"

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name) do { printf("  TEST: %s ... ", name); } while(0)
#define PASS() do { printf("PASS\n"); tests_passed++; } while(0)
#define FAIL(msg) do { printf("FAIL: %s\n", msg); tests_failed++; } while(0)

static void test_push_String(void) {
    String_list_link *head = Init_String("first", 5);
    assert(head != NULL && "Init_String failed");
    String_list_link *p;

    p = push_String(head, "second", 6);
    assert(p != NULL);
    assert(p->size_string == 6);
    assert(strcmp(p->string_action.string, "second") == 0);

    p = push_String(head, "third", 5);
    assert(p != NULL);
    assert(p->size_string == 5);
    assert(strcmp(p->string_action.string, "third") == 0);

    int count = 0;
    for (String_list_link *i = head; i != NULL; i = i->next_string)
        count++;
    assert(count == 3);
    PASS();
}

static void test_pop_List_instrution_v2(void) {
    List_instrution *list = init_List_instrution();
    assert(list != NULL);
    list->id = 0;

    size_t const N = 5;
    List_instrution *nodes[N];
    nodes[0] = list;
    for (size_t i = 1; i < N; i++) {
        nodes[i] = push_List_instrution(list);
        assert(nodes[i] != NULL);
    }
    assert(get_number_instrutions(list) == N);

    List_instrution *result;

    result = pop_List_instrution_v2(list, 0);
    assert(result != NULL);
    assert(get_number_instrutions(result) == N - 1);
    list = result;

    result = pop_List_instrution_v2(list, 2);
    assert(result != NULL);
    assert(get_number_instrutions(result) == N - 2);
    list = result;

    result = pop_List_instrution_v2(list, 999);
    assert(result == NULL);

    PASS();
}

static void test_get_number_instrutions(void) {
    List_instrution *list = init_List_instrution();
    assert(list != NULL);
    assert(get_number_instrutions(list) == 1);

    push_List_instrution(list);
    assert(get_number_instrutions(list) == 2);

    push_List_instrution(list);
    assert(get_number_instrutions(list) == 3);

    pop_List_instrution_v2(list, 1);
    assert(get_number_instrutions(list) == 2);

    assert(get_number_instrutions(NULL) == 0);
    PASS();
}

static void test_format_instruccion(void) {
    uint8_t bytes[] = {
        0x00, 0xc0,  /* add al, al  (16-bit encoding) */
        0x01, 0xd6,  /* add si, dx  (16-bit)          */
        0x04, 0x10,  /* add al, 0x10                  */
    };
    size_t n = sizeof(bytes);

    List_instrution *list = format_instruccion(bytes, n, ENCODER_IN_16bits);
    assert(list != NULL);
    size_t count = get_number_instrutions(list);
    if (count == 0) {
        FAIL("no instructions decoded");
        return;
    }
    assert(count > 0);
    PASS();
}

static void test_get_size_to_String(void) {
    String_list_link *list = Init_String("hello", 5);
    assert(list != NULL);
    push_String(list, " world", 6);
    size_t sz = get_size_to_String(list);
    assert(sz == 11);
    sz = get_size_to_String(NULL);
    assert(sz == SIZE_MAX);
    PASS();
}

static void test_get_number_nodes_String_list_link(void) {
    String_list_link *list = Init_String("a", 1);
    assert(list != NULL);
    push_String(list, "b", 1);
    push_String(list, "c", 1);
    assert(get_number_nodes_String_list_link(list) == 3);
    assert(get_number_nodes_String_list_link(NULL) == SIZE_MAX);
    PASS();
}

int main(void) {
    printf("opcodes-fork test suite\n");
    printf("======================\n\n");

    TEST("push_String appends correctly");
    test_push_String();

    TEST("pop_List_instrution_v2 at various positions");
    test_pop_List_instrution_v2();

    TEST("get_number_instrutions");
    test_get_number_instrutions();

    TEST("format_instruccion with known byte sequences");
    test_format_instruccion();

    TEST("get_size_to_String returns correct sizes");
    test_get_size_to_String();

    TEST("get_number_nodes_String_list_link");
    test_get_number_nodes_String_list_link();

    printf("\nResults: %d passed, %d failed out of %d\n",
           tests_passed, tests_failed, tests_passed + tests_failed);

    return tests_failed > 0 ? 1 : 0;
}
