import random
def hill_climbing():
    def generate_board():
        return random.sample(range(8), 8)
    def count_attacking_pairs(pos):
        atk = 0
        for i in range(7):
            for j in range(i + 1, 8):
                if pos[i] == pos[j] or abs(pos[i] - pos[j]) == j - i:
                    atk += 1
        return atk
    def get_neighbor(pos):
        new_pos = list(pos)
        i, j = random.sample(range(8), 2)
        new_pos[i], new_pos[j] = new_pos[j], new_pos[i]
        return new_pos
    current_pos = generate_board()
    current_atk = count_attacking_pairs(current_pos)
    
    while current_atk > 0:
        next_pos = get_neighbor(current_pos)
        next_atk = count_attacking_pairs(next_pos)
        
        if next_atk < current_atk:
            current_pos = next_pos
            current_atk = next_atk
        elif next_atk == current_atk:
            current_pos = next_pos
    return current_pos
final_state = hill_climbing()
print(f"Final Position: {final_state}")