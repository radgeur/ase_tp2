#include "swtch_ctx.h"

static struct ctx_s *current_ctx = NULL;

static void start_current_ctx (void) {
  current_ctx->ctx_state = CTX_EXEQ;
  current_ctx->ctx_F(current_ctx->ctx_args);
  current_ctx->ctx_state = CTX_END;
  printf ("une des fonctions est terminée\n");
  exit(EXIT_SUCCESS);
}


void init_ctx(struct ctx_s *ctx, int stack_size, func_t *f, void *args) {
  ctx->ctx_F = f;
  ctx->ctx_args = args;
  ctx->ctx_magic = CTX_MAGIC;
  ctx->ctx_state = CTX_INIT;
  ctx->ctx_base = malloc(stack_size);
  ctx->ctx_esp = ctx->ctx_ebp = ctx->ctx_base + stack_size - 4;
}


void switch_to_ctx (struct ctx_s *ctx) {
  assert (ctx->ctx_magic == CTX_MAGIC);

  assert (ctx->ctx_state == CTX_INIT || ctx->ctx_state == CTX_EXEQ);
  
  if (current_ctx)
    asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       : "=r"(current_ctx->ctx_esp) , "=r"(current_ctx->ctx_ebp)
       : );

  current_ctx = ctx;
  
  asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
      :
      :"r"(current_ctx->ctx_esp), "r"(current_ctx->ctx_ebp));

  if (current_ctx->ctx_state == CTX_INIT)
    start_current_ctx();
}
