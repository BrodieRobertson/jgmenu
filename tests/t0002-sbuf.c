#include "../sbuf.h"
#include "../list.h"

static char test_name[] = "test0002-sbuf";
static int verbose = 0;

int main(void)
{
	int i;
	struct String s;

	sbuf_init(&s);
	for (i = 0; i < 5; i++) {
		sbuf_addch(&s, 'A' + i);
	}
	
	sbuf_addstr(&s, "FGHIJKLMNO");
	sbuf_addch(&s, 'P');
	sbuf_addch(&s, 'Q');
	sbuf_addstr(&s, "R");

	if (verbose) {
		printf("test:%s\n", s.buf);
		printf("length:%d\n", s.len);
		printf("allocated:%d\n", s.bufsiz);
	}

	if (!strcmp(s.buf, "ABCDEFGHIJKLMNOPQR") &&
	    s.len == 18 &&
	    s.bufsiz == 19) {
		printf("[PASS] %s\n", test_name);
	} else {
		printf("[FAIL] %s\n", test_name);
		return 1;
	}



	printf("\nString List Test:\n");

	struct list_head sl;	/* String List */
	struct String *tmp;	/* temp string for the for_each loop */

	INIT_LIST_HEAD(&sl);
	sbuf_list_append(&sl, "zero");
	sbuf_list_append(&sl, "one");
	sbuf_list_append(&sl, "two");
	sbuf_list_append(&sl, "three");
	
	i = 0;
	list_for_each_entry(tmp, &sl, list)
		printf("list-item-%d: %s\n", i++, tmp->buf);

	printf("\n");

	return 0;
}
