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

typedef void (*op_handler)(struct lc3 *, uint16_t);

typedef struct {
	int idx;
	op_handler func;
} instruction;

static uint16_t extract_dr(uint16_t);
static uint16_t extract_sr1(uint16_t);
static uint16_t extract_sr2(uint16_t);
static int is_imm_mode(uint16_t);

static void op_br(struct lc3 *, uint16_t);
static void op_add(struct lc3 *, uint16_t);
static void op_ld(struct lc3 *, uint16_t);
static void op_st(struct lc3 *, uint16_t);
static void op_jsr(struct lc3 *, uint16_t);
static void op_and(struct lc3 *, uint16_t);
static void op_ldr(struct lc3 *, uint16_t);
static void op_str(struct lc3 *, uint16_t);
static void op_rti(struct lc3 *, uint16_t);
static void op_not(struct lc3 *, uint16_t);
static void op_ldi(struct lc3 *, uint16_t);
static void op_sti(struct lc3 *, uint16_t);
static void op_jmp(struct lc3 *, uint16_t);
static void op_res(struct lc3 *, uint16_t);
static void op_lea(struct lc3 *, uint16_t);
static void op_trap(struct lc3 *, uint16_t);

static instruction
optable[0x10] = {
	{ .idx = OP_BR, .func = op_br },
	{ .idx = OP_ADD, .func = op_add },
	{ .idx = OP_LD, .func = op_ld },
	{ .idx = OP_ST, .func = op_st },
	{ .idx = OP_JSR, .func = op_jsr },
	{ .idx = OP_AND, .func = op_and },
	{ .idx = OP_LDR, .func = op_ldr },
	{ .idx = OP_STR, .func = op_str },
	{ .idx = OP_RTI, .func = op_rti },
	{ .idx = OP_NOT, .func = op_not },
	{ .idx = OP_LDI, .func = op_ldi },
	{ .idx = OP_STI, .func = op_sti },
	{ .idx = OP_JMP, .func = op_jmp },
	{ .idx = OP_RES, .func = op_res },
	{ .idx = OP_LEA, .func = op_lea },
	{ .idx = OP_TRAP, .func = op_trap }
};

static uint16_t
extract_dr(uint16_t instr)
{
	return (instr >> 9) & 0x7; /* mask 3 bits */
}

static uint16_t
extract_sr1(uint16_t instr)
{
	return (instr >> 6) & 0x7; /* mask 3 bits */
}

static uint16_t
extract_sr2(uint16_t instr)
{
	return instr & 0x7; /* mask 3 bits */
}

static int
is_imm_mode(uint16_t instr)
{
	return (instr >> 5) & 0x1; /* mask 1 bit */
}

static void
op_br(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_add(struct lc3 *lc3, uint16_t instr)
{
	uint16_t dr = extract_dr(instr);
	uint16_t sr1 = extract_sr1(instr);
	int imm_mode = is_imm_mode(instr);

	if (imm_mode) {
	} else {
	}
}

static void
op_ld(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_st(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_jsr(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_and(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_ldr(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_str(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_rti(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_not(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_ldi(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_sti(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_jmp(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_res(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_lea(struct lc3 *lc3, uint16_t instr)
{
}

static void
op_trap(struct lc3 *lc3, uint16_t instr)
{
}

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
	uint16_t instr;

	reset(&lc3);
	/* load rom */

	while (lc3.running) {
		instr = memread(&lc3, lc3.pc++);
		optable[instr >> 12].func(&lc3, instr);
	}

	return 0;
}
