
n = eval(input())

recipes = []
for i in range(n):
    recipes.append(set([int(ing) for ing in input().split(' ')][1:]))

consumed = set()
cauldrons = set()
num_recipes = 0

for recipe in recipes:

    if len(recipe & consumed) == 0:
        num_recipes += 1
        consumed |= recipe
        cauldrons.add(frozenset(recipe))
        continue

    removed_cauldrons = set()
    final_recipe = recipe
    for cauldron in cauldrons:
        intersect = cauldron & recipe
        if intersect == cauldron:
            recipe ^= cauldron
            removed_cauldrons.add(cauldron)
        elif len(intersect) > 0:
            break

        if len(recipe) == 0:
            break

    if len(recipe & consumed) == 0:
        num_recipes += 1
        consumed |= recipe
        cauldrons.add(frozenset(final_recipe))
        cauldrons ^= removed_cauldrons


print(num_recipes)