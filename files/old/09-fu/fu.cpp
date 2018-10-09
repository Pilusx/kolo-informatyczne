#define N 500005

int father[N];
int size[N];

// Na poczatku size[i] = 1, father[i] = i

int Find(int x) {
  if (father[x] == x)
    return x;
  else
    father[x] = Find(father[x]);
  return father[x];
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (a == b)
    return;
  if (size[a] < size[b]) {
    size[b] += size[a];
    father[a] = b;
  } else {
    size[a] += size[b];
    father[b] = a;
  }
}
