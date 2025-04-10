#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *buffer;
  int size;
  int head;
  int tail;
  bool full;
} RingBuffer;

void initBuffer(RingBuffer *rb, int size) {
  rb->buffer = malloc(sizeof(int) * size);
  rb->head = 0;
  rb->tail = 0;
  rb->full = false;
  rb->size = size;
}

bool isEmpty(RingBuffer *rb) { return (!rb->full && rb->head == rb->tail); }

bool isFull(RingBuffer *rb) { return rb->full; }

void enqueue(RingBuffer *rb, int value) {
  if (isFull(rb)) {
    printf("Buffer is full. Overwriting oldest data\n");
    rb->head = (rb->head + 1) % rb->size;
  }
  rb->buffer[rb->tail] = value;
  rb->tail = (rb->tail + 1) % rb->size;
  if (rb->head == rb->tail) {
    rb->full = true;
  }
}

int dequeue(RingBuffer *rb) {
  if (isEmpty(rb)) {
    printf("Buffer is empty\n");
    return -1; // Error code
  }
  int result = rb->buffer[rb->head];
  rb->head = (rb->head + 1) % rb->size;
  rb->full = false;
  return result;
}

void printBuffer(RingBuffer *rb) {
  printf("Buffer: ");
  for (int i = 0; i < rb->size; i++) {
    printf("%d ", rb->buffer[i]);
  }
  printf("\nHead: %d, Tail: %d, Full: %s\n", rb->head, rb->tail,
         rb->full ? "true" : "false");
}

int main(void) {
  RingBuffer rb;
  initBuffer(&rb, 5);

  enqueue(&rb, 10);
  enqueue(&rb, 20);
  enqueue(&rb, 30);
  enqueue(&rb, 40);
  enqueue(&rb, 50);

  // Overwrite oldest
  enqueue(&rb, 60);
  printBuffer(&rb);

  printf("Dequeue: %d\n", dequeue(&rb));
  printf("Dequeue: %d\n", dequeue(&rb));

  printBuffer(&rb);

  return 0;
}
