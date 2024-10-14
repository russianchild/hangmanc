#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 100


struct HangmanGame {
    char word[MAX_WORD_LENGTH];        
    char guessedWord[MAX_WORD_LENGTH]; 
    char guessedLetters[26];           
    int tries;                         
};

void initializeGame(struct HangmanGame *game, const char *word) {
    strcpy(game->word, word);
    memset(game->guessedWord, '_', strlen(word)); 
    game->guessedWord[strlen(word)] = '\0'; 
    memset(game->guessedLetters, 0, sizeof(game->guessedLetters)); 
    game->tries = 0; // Reset tries
}

void displayState(const struct HangmanGame *game) {
    printf("\nCurrent word: %s\n", game->guessedWord);
    printf("Guessed letters: ");
    for (int i = 0; i < 26; i++) {
        if (game->guessedLetters[i]) {
            printf("%c ", 'A' + i);
        }
    }
    printf("\n");
}

int isWordGuessed(const struct HangmanGame *game) {
    return strcmp(game->word, game->guessedWord) == 0;
}

void guessLetter(struct HangmanGame *game, char guess) {
    int correctGuess = 0;

    for (int i = 0; i < strlen(game->word); i++) {
        if (game->word[i] == guess) {
            game->guessedWord[i] = guess; 
            correctGuess = 1; 
        }
    }

    if (!correctGuess) {
        game->tries++; 
        printf("Wrong guess! You have %d tries left.\n", MAX_TRIES - game->tries);
    }
}

int main() {
    struct HangmanGame game;
    const char *word = "mastersid"; 

    initializeGame(&game, word);
    printf("Welcome to Hangman!\n");

    while (game.tries < MAX_TRIES) {
        displayState(&game);
        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess); 

        if (game.guessedLetters[guess - 'a']) {
            printf("You've already guessed that letter!\n");
            continue;
        }

        game.guessedLetters[guess - 'a'] = 1; 
        guessLetter(&game, guess);

        if (isWordGuessed(&game)) {
            printf("Congratulations! You've guessed the word: %s\n", game.word);
            return 0;
        }
    }

    printf("Game Over! The word was: %s\n", game.word);
return 0;
}