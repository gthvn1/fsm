#include <stdio.h>
#include <string.h>

// Implement the simple FSM described by https://en.wikipedia.org/wiki/Finite-state_machine

#define LOCKED_STATE "locked"
#define UNLOCKED_STATE "unlocked"

struct fsm_state_t; // Forward declaration

enum fsm_event_t
{
	EVENT_NONE,
	EVENT_EXIT,
	EVENT_PUSH,
	EVENT_COIN
};

typedef void (*fsm_state_fn)(struct fsm_state_t *state, enum fsm_event_t event);

struct fsm_state_t
{
	char *name;
	fsm_state_fn handler;
};

void locked_handler(struct fsm_state_t *state, enum fsm_event_t event);
void unlocked_handler(struct fsm_state_t *state, enum fsm_event_t event);

void locked_handler(struct fsm_state_t *state, enum fsm_event_t event)
{
	if (event == EVENT_COIN)
	{
		state->name = UNLOCKED_STATE;
		state->handler = unlocked_handler;
	}
}

void unlocked_handler(struct fsm_state_t *state, enum fsm_event_t event)
{
	if (event == EVENT_PUSH)
	{
		state->name = LOCKED_STATE;
		state->handler = locked_handler;
	}
}

#define MAXSIZE 32
enum fsm_event_t get_event(void)
{
	char input[MAXSIZE];

	printf("Enter push, coin or exit: ");
	scanf("%s", input);

	if (strncmp(input, "push", MAXSIZE) == 0)
		return EVENT_PUSH;
	else if (strncmp(input, "coin", MAXSIZE) == 0)
		return EVENT_COIN;
	else if (strncmp(input, "exit", MAXSIZE) == 0)
		return EVENT_EXIT;

	return EVENT_NONE;
}

void run_fsm(void)
{
	struct fsm_state_t state;
	enum fsm_event_t event;

	state.name = LOCKED_STATE;
	state.handler = locked_handler;

	while (1)
	{
		printf("Current state -> %s\n", state.name);

		switch (event = get_event())
		{
		case EVENT_NONE:
			printf("Unknwon event\n");
			break;
		case EVENT_EXIT:
			return;
		default:
			state.handler(&state, event);
		}
	}
}

int main(void)
{
	run_fsm();
	printf("Bye\n");
	return 0;
}
