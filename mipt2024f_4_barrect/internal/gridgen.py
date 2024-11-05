import cv2
import numpy
import numpy as np
from .gridmap import GridMap


def rect_grid(border: np.ndarray, dest_width: int, dest_height: int) -> GridMap:
    dest_grid = np.int32(
        [
            [0, dest_height],
            [dest_width, dest_height],
            [dest_width, 0],
            [0, 0]
        ]
    )

    return GridMap(border, dest_grid)


def bent_corner_grid(
        border: np.ndarray,
        corner_idx: int,
        dest_width: int,
        dest_height: int
) -> GridMap:
    dest_grid = [
        [0, dest_height],
        [dest_width, dest_height],
        [dest_width, 0],
        [0, 0]
    ]

    prev_vect = border[(corner_idx + 4) % 6] - border[(corner_idx + 5) % 6]
    next_vect = border[(corner_idx + 1) % 6] - border[(corner_idx + 2) % 6]

    prev_opposite = border[(corner_idx + 2) % 6] - border[(corner_idx + 3) % 6]
    next_opposite = border[(corner_idx + 3) % 6] - border[(corner_idx + 4) % 6]

    bent_real_idx = (corner_idx + 1) // 2
    real = dest_grid[bent_real_idx]
    prev_vect_real = np.int32(dest_grid[(bent_real_idx + 3) % 4]) - np.int32(dest_grid[bent_real_idx])
    next_vect_real = np.int32(dest_grid[(bent_real_idx + 1) % 4]) - np.int32(dest_grid[bent_real_idx])

    prev_dest = real + prev_vect_real * (1 - cv2.norm(prev_vect) / cv2.norm(prev_opposite))
    next_dest = real + next_vect_real * (1 - cv2.norm(next_vect) / cv2.norm(next_opposite))

    return GridMap(border, np.int32(dest_grid))
