#include <stdint.h>
#include <stdio.h>

enum {
	RAM_SIZE = (1 << 16)
};

enum {
	PC_START = 0x3000
};

enum {
	OP_BR = 0, /* 0: branch */
	OP_ADD,    /* 1: addition */
	OP_LD,     /* 2: load */
	OP_ST,     /* 3: store */
	OP_JSR,    /* 4: jump register */
	OP_AND,    /* 5: bitwise and */
	OP_LDR,    /* 6: load register */
	OP_STR,    /* 7: store register */
	OP_RTI,    /* 8: unused */
	OP_NOT,    /* 9: bitwise not */
	OP_LDI,    /* A: load indirect */
	OP_STI,    /* B: store indirect */
	OP_JMP,    /* C: jump */
	OP_RES,    /* D: reserved */
	OP_LEA,    /* E: load effective address */
	OP_TRAP    /* F: execute trap */
};

enum {
	FL_POS = 1 << 0, /* Positive */
	FL_ZRO = 1 << 1, /* Zero */
	FL_NEG = 1 << 2  /* Negative */
};

struct lc3 {
	uint16_t r0;
	uint16_t r1;
	uint16_t r2;
	uint16_t r3;
	uint16_t r4;
	uint16_t r5;
	uint16_t r6;
	uint16_t r7;
	uint16_t pc;
	uint16_t flags;
	uint16_t ram[RAM_SIZE];
	int running;
};

static void
memwrite(struct lc3 *lc3, uint16_t addr, uint16_t val)
{
	lc3->ram[addr] = val;
}

static uint16_t
memread(struct lc3 *lc3, uint16_t addr)
{
	return lc3->ram[addr];
}

static void
reset(struct lc3 *lc3)
{
	lc3->pc = PC_START;
	lc3->running = 1;
}

static void
upd_flags(struct lc3 *lc3, uint16_t r)
{
	if (r == 0) lc3->flags = FL_ZRO;
	else if (r >> 15) lc3->flags = FL_NEG;
	else lc3->flags = FL_POS;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: lc3 imagefile\n");
		return 1;
	}

	struct lc3 lc3 = {0};
	reset(&lc3);

	/* load rom */

	while (lc3.running) {
		uint16_t instr = memread(&lc3, lc3.pc++);
		uint16_t op = instr >> 12;

		switch (op) {
		}
	}

	return 0;
}
