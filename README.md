# cub3d

> A compact **cub3d** setup with core sources, project headers, and a vendored `libft`.

---

## ✨ At a glance

- Language: **C**
- Build system: **Makefile**
- Local library: **`includes/libft/`**
- Graphics dependency: **MiniLibX** (`minilibx/`)

---

## 📁 Project layout

```text
.
├── Makefile
├── includes/
│   ├── cub3d.h
│   ├── libft.h
│   └── libft/
└── src/
    ├── main.c
    └── raycasting.c
```

| Path | Purpose |
|---|---|
| `src/` | Main game source files (`main.c`, `raycasting.c`). |
| `includes/` | Project headers. |
| `includes/libft/` | Vendored `libft` source + its Makefile. |
| `Makefile` | Builds `libft`, prepares MiniLibX, then links `cub3d`. |

---

## 🛠️ Build

```bash
make
```

Build flow:

1. Build `libft` from `includes/libft`.
2. Clone `minilibx` if it does not exist.
3. Build MiniLibX.
4. Compile and link the final `cub3d` binary.

---

## ⚠️ Environment note

In restricted environments, `make` may fail while cloning MiniLibX if GitHub access is blocked.
