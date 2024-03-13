import random
import math
from typing import List

def get_character_set(options: List[bool]) -> str:
    character_set = ""
    for i, include in enumerate(options):
        if include:
            character_set += CHARACTER_SETS[i]
    return character_set

def calculate_combinations(options: List[bool]) -> float:
    combinations = 1
    for i, include in enumerate(options):
        if include:
            combinations *= len(CHARACTER_SETS[i])
    return combinations

def calculate_entropy(combinations: float) -> float:
    return math.log2(calculate_combinations(options)) * len(password)

def calculate_password_length(entropy: float, options: List[bool]) -> int:
    return math.ceil(entropy / math.log2(calculate_combinations(options)))

def generate_password(length: int, character_set: str) -> str:
    password = ""
    for _ in range(length):
        password += random.choice(character_set)
    return password