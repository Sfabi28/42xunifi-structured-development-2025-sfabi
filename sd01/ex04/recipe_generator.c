#include "recipe_generator.h"

struct Recipe *create_custom_recipe(void)
{
    while (1) {
        struct Ingredients *ingredients = get_current_ingredients();
        if (!ingredients)
            return NULL;

        struct TasteProfile *profile = get_user_taste_profile();
        if (!profile) {
            free_ingredients(ingredients);
            return NULL;
        }

        struct Recipe *recipe = create_recipe(ingredients, profile);
        if (!recipe) {
            free_ingredients(ingredients);
            free_taste_profile(profile);
            return NULL;
        }

        free_ingredients(ingredients);
        free_taste_profile(profile);

        int approved = get_user_approval(recipe);
        
        if (approved)
            return recipe;

        free_recipe(recipe);
    }
}