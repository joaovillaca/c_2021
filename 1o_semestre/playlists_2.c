/*
    @author João Villaça - 10724239
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug 0

#define NOTPLAYING    -1
#define ERROR          1
#define SUCCESS        0

#define ADDSONG        1
#define SHOW_PLAYLIST  2
#define NEXTSONG       3
#define PREVSONG       4
#define SAVE           5
#define LOAD           6
#define HALT           7

// ==================================================================================

typedef struct _SONG {
    char*  name;
    char*  artist;
    int    timeInSeconds;
} Song;

Song*  NewSong               (int* errorFlag);
void   SetSongName           (Song* target, char* setname, int* errorFlag);
void   SetSongArtist         (Song* target, char* setname, int* errorFlag);
void   SetSongTimeInSec      (Song* target, int time, int* errorFlag);
char*  GetSongName           (Song* target, int* errorFlag);
char*  GetSongArtist         (Song* target, int* errorFlag);
int    GetSongTimeInSeconds  (Song* target, int* errorFlag);

// ==================================================================================

typedef struct _PLAYLIST {
    char*   name;
    int     size;
    Song**  Items;
    Song*   NowPlaying;
    int     NowPlayingIndex;
} Playlist;

Playlist* NewPlaylist        (int* errorFlag);
void      SetPlaylistName    (Playlist* target, char* setname, int* errorFlag);
char*     GetPlaylistName    (Playlist* target, int* errorFlag);
int       GetPlaylistSize    (Playlist* target, int* errorFlag);
void      AddSongToPlaylist  (Playlist* dest, Song* target, int* errorFlag);
int       NextSong           (Playlist* target, int* errorFlag);
int       PreviousSong       (Playlist* target, int* errorFlag);
void      ErasePlaylist      (Playlist* MyPlaylist);
void      SavePlaylist       (Playlist* MyPlaylist, FILE* fp);
Playlist* LoadPlaylist       (FILE* fp);

// ==================================================================================

char* ReadLine    (int bufferSize, int* errorFlag);
void  binaryToNum (char *binFilename);

int main(int argc, char** argv) {

    int comando = 0;
    int error_trigger = 0;

    Playlist* MyPlaylist = NewPlaylist(&error_trigger);
    if(error_trigger) {
        puts("Erro ao alocar a playlist.");
        return 0;
    }

    char* nome = NULL;
    nome = ReadLine(8, &error_trigger);
    SetPlaylistName(MyPlaylist, nome, &error_trigger);
    if(error_trigger) {
        puts("Erro ao colocar nome na playlist.");
        return 0;
    }

    char* songname;
    char* artistname;
    int timestamp;

    char* filename = NULL;
    FILE* filehandler = NULL;

    do {
        scanf("%d", &comando);
        getchar();
        switch (comando) {

            case ADDSONG:
                if(MyPlaylist->size == 15) {
                    puts("Playlist cheia!");
                    continue;
                }
                songname = ReadLine(8, &error_trigger);
                artistname = ReadLine(8, &error_trigger);
                scanf("%d", &timestamp);
                getchar();
                Song* newsong = NewSong(&error_trigger);
                SetSongName(newsong, songname, &error_trigger);
                SetSongArtist(newsong, artistname, &error_trigger);
                SetSongTimeInSec(newsong, timestamp, &error_trigger);
                AddSongToPlaylist(MyPlaylist, newsong, &error_trigger);
                if(error_trigger) {
                    puts("Erro ao adicionar a música.");
                }
                printf("Musica %s de %s adicionada com sucesso.\n",
                GetSongName(newsong, &error_trigger), GetSongArtist(newsong, &error_trigger));
                if(MyPlaylist->size == 1) {
                    NextSong(MyPlaylist, &error_trigger);
                }
                break;
            
            case SHOW_PLAYLIST:
                printf("---- Playlist: %s ----\n", GetPlaylistName(MyPlaylist, &error_trigger));
                printf("Total de musicas: %d\n", GetPlaylistSize(MyPlaylist, &error_trigger));
                for(int i = 0; i < GetPlaylistSize(MyPlaylist, &error_trigger); i++) {
                    printf("\n");
                    if(i == MyPlaylist->NowPlayingIndex) {
                        puts("=== NOW PLAYING ===");
                    }
                    printf("(%d). '%s'\n", i+1, GetSongName(MyPlaylist->Items[i], &error_trigger));
                    printf("Artista: %s\n", GetSongArtist(MyPlaylist->Items[i], &error_trigger));
                    printf("Duracao: %d segundos\n", GetSongTimeInSeconds(MyPlaylist->Items[i], &error_trigger));
                }
                printf("\n");
                break;

            case NEXTSONG:
                NextSong(MyPlaylist, &error_trigger);
                if(error_trigger) {
                    puts("Erro ao passar para a proxima musica.");
                }
                break;

            case PREVSONG:
                PreviousSong(MyPlaylist, &error_trigger);
                if(error_trigger) {
                    puts("Erro ao passar para a musica anterior.");
                }
                break;

            case SAVE:
                filename = ReadLine(8, &error_trigger);
                filehandler = fopen(filename, "wb");
                SavePlaylist(MyPlaylist, filehandler);
                fclose(filehandler);
                printf("Playlist %s salva com sucesso.\n", filename);
                binaryToNum(filename);
                break;
            
            case LOAD:
                filename = ReadLine(8, &error_trigger);
                filehandler = fopen(filename, "rb");
                if(filehandler == NULL) {
                    printf("Arquivo %s nao existe.\n", filename);
                    return 0;
                }
                ErasePlaylist(MyPlaylist);
                MyPlaylist = LoadPlaylist(filehandler);
                fclose(filehandler);
                printf("Playlist %s carregada com sucesso.\n", filename);
                binaryToNum(filename);
                break;

            case HALT:
                break;

            default:
                printf("Comando desconhecido. Digite %d para sair.", HALT);
                continue;
        }
    } while(comando != HALT);

    ErasePlaylist(MyPlaylist);
    return 0;
}

// ==================================================================================

void SavePlaylist(Playlist* MyPlaylist, FILE* fp) {
    if(MyPlaylist == NULL || fp == NULL) {
        return;
    }

    int plsize = (int) strlen(MyPlaylist->name);
    fwrite(&plsize, sizeof(int), 1, fp);
    fwrite(MyPlaylist->name, sizeof(char), plsize, fp);
    fwrite(&MyPlaylist->size, sizeof(int), 1, fp);

    int song_name_size = 0;
    int artist_name_size = 0;

    for(int i = 0; i < MyPlaylist->size; i++) {
        song_name_size = (int) strlen(MyPlaylist->Items[i]->name);
        artist_name_size = (int) strlen(MyPlaylist->Items[i]->artist);
        fwrite(&song_name_size, sizeof(int), 1, fp);
        fwrite(MyPlaylist->Items[i]->name, sizeof(char), song_name_size, fp);
        fwrite(&artist_name_size, sizeof(int), 1, fp);
        fwrite(MyPlaylist->Items[i]->artist, 1, artist_name_size, fp);
        fwrite(&MyPlaylist->Items[i]->timeInSeconds, sizeof(int), 1, fp);
    }
}

Playlist* LoadPlaylist(FILE* fp) {
    if(fp == NULL) {
        return NULL;
    }

    int err = 0;
    Playlist* new = NewPlaylist(&err);

    int namesize = 0;
    fread(&namesize, sizeof(int), 1, fp);
    char* name = NULL;
    name = (char*) malloc((namesize + 1) * sizeof(char));
    name[namesize] = '\0';
    fread(name, sizeof(char), namesize, fp);
    SetPlaylistName(new, name, &err);

    int size = 0;
    fread(&size, sizeof(int), 1, fp);
    new->size = size;

    Song* pointer = NULL;
    int artist_name_size = 0;
    for(int i = 0; i < size; i++) {
        pointer = NewSong(&err);
        fread(&namesize, sizeof(int), 1, fp);
        name = (char*) malloc((namesize + 1) * sizeof(char));
        for(int j = 0; j < namesize; j++) {
            fread(&name[j], sizeof(char), 1, fp);
        }
        name[namesize] = '\0';
        SetSongName(pointer, name, &err);
        fread(&artist_name_size, sizeof(int), 1, fp);
        name = (char*) malloc((artist_name_size + 1) * sizeof(char));
        for(int j = 0; j < artist_name_size; j++) {
            fread(&name[j], sizeof(char), 1, fp);
        }
        name[artist_name_size] = '\0';
        SetSongArtist(pointer, name, &err);
        fread(&pointer->timeInSeconds, sizeof(int), 1, fp);
        AddSongToPlaylist(new, pointer, &err);
    }
    return new;
}

Song* NewSong(int* errorFlag) {
    Song* _song = NULL;
    _song = (Song*) malloc(sizeof(Song));
    if(_song == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    _song->name = NULL;
    _song->artist = NULL;
    _song->timeInSeconds = 0;
    *errorFlag = SUCCESS;
    return _song;
}

void SetSongName(Song* target, char* setname, int* errorFlag) {
    if(target == NULL || setname == NULL) {
        *errorFlag = ERROR;
        return;
    }
    if(target->name != NULL) {
        free(target->name);
    }
    target->name = setname;
    *errorFlag = SUCCESS;
    return;
}

void SetSongArtist(Song* target, char* setname, int* errorFlag) {
    if(target == NULL || setname == NULL) {
        *errorFlag = ERROR;
        return;
    }
    if(target->artist != NULL) {
        free(target->artist);
    }
    target->artist = setname;
    *errorFlag = SUCCESS;
    return;
}

void SetSongTimeInSec(Song* target, int time, int* errorFlag) {
    if(target == NULL || time <= 0) {
        *errorFlag = ERROR;
        return;
    }
    target->timeInSeconds = time;
    *errorFlag = SUCCESS;
    return;
}

char* GetSongName(Song* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    if(target->name == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    *errorFlag = SUCCESS;
    return target->name;
}

char* GetSongArtist(Song* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    if(target->artist == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    *errorFlag = SUCCESS;
    return target->artist;
}

int GetSongTimeInSeconds(Song* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return 0;
    }
    if(target->timeInSeconds <= 0) {
        *errorFlag = ERROR;
        return target->timeInSeconds;
    }
    *errorFlag = SUCCESS;
    return target->timeInSeconds;
}

// ==================================================================================

Playlist* NewPlaylist(int* errorFlag) {
    Playlist* _playlist = NULL;
    _playlist = (Playlist*) malloc(sizeof(Playlist));
    if(_playlist == NULL) {
        *errorFlag = ERROR;
        return NULL;
    } 
    _playlist->name = NULL;
    _playlist->size = 0;
    _playlist->Items = NULL;
    _playlist->NowPlaying = NULL;
    _playlist->NowPlayingIndex = NOTPLAYING;
    *errorFlag = SUCCESS;
    return _playlist;
}

void ErasePlaylist(Playlist* MyPlaylist) {
    if(MyPlaylist == NULL) {
        return;
    }
    for(int i = 0; i < MyPlaylist->size; i++) {
        free(MyPlaylist->Items[i]->name);
        free(MyPlaylist->Items[i]->artist);
        free(MyPlaylist->Items[i]);
    }
    free(MyPlaylist->Items);
    free(MyPlaylist->name);
    free(MyPlaylist);
}

void SetPlaylistName(Playlist* target, char* setname, int* errorFlag) {
    if(target == NULL || setname == NULL) {
        *errorFlag = ERROR;
        return;
    }
    if(target->name != NULL) {
        free(target->name);
    }
    target->name = setname;
    *errorFlag = SUCCESS;
    return;
}

char* GetPlaylistName(Playlist* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    if(target->name == NULL) {
        *errorFlag = ERROR;
        return NULL;
    }
    *errorFlag = SUCCESS;
    return target->name;
}

int GetPlaylistSize(Playlist* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return 0;
    }
    if(target->size < 0 || target->size > 15) {
        *errorFlag = ERROR;
        return target->size;
    }
    *errorFlag = SUCCESS;
    return target->size;
}

void AddSongToPlaylist(Playlist* dest, Song* target, int* errorFlag) {
    if(dest == NULL || target == NULL) {
        *errorFlag = ERROR;
        return;
    }
    if(dest->size > 15 || dest->size < 0) {
        *errorFlag = ERROR;
        return;
    }
    if(dest->size == 15) {
        *errorFlag = SUCCESS;
        return;
    }
    dest->Items = (Song**) realloc(dest->Items, (dest->size + 1) * sizeof(Song*));
    if(dest->Items == NULL) {
        *errorFlag = ERROR;
        return;
    }
    dest->Items[dest->size] = (Song*) malloc(sizeof(Song));
    if(dest->Items[dest->size] == NULL) {
        *errorFlag = ERROR;
        return;
    }
    dest->Items[dest->size] = target; 
    *errorFlag = SUCCESS;
    dest->size++;
    return;
}

// @return SUCCESS se passar de música, ERROR se não conseguir, NOTPLAYING se a playlist acabou
// se não começou, toca a primeira música
int NextSong(Playlist* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return ERROR;
    }
    if(target->size > 15 || target->size <= 0) {
        *errorFlag = ERROR;
        return ERROR;
    }
    if(target->NowPlaying == NULL) {
        target->NowPlaying = target->Items[0];
        target->NowPlayingIndex = 0;
        *errorFlag = SUCCESS;
        return SUCCESS;
    }
    if(target->NowPlaying == target->Items[target->size - 1]) {
        target->NowPlaying = NULL;
        target->NowPlayingIndex = NOTPLAYING;
        *errorFlag = SUCCESS;
        return NOTPLAYING;
    }
    target->NowPlaying = target->Items[target->NowPlayingIndex + 1];
    target->NowPlayingIndex += 1;
    *errorFlag = SUCCESS;
    return SUCCESS;
}

// @return SUCCESS se voltar de música, ERROR se não conseguir, NOTPLAYING voltar na primeira musica
// se não começou, toca a ultima música
int PreviousSong(Playlist* target, int* errorFlag) {
    if(target == NULL) {
        *errorFlag = ERROR;
        return ERROR;
    }
    if(target->size > 15 || target->size <= 0) {
        *errorFlag = ERROR;
        return ERROR;
    }
    if(target->NowPlaying == NULL) {
        target->NowPlaying = target->Items[target->size];
        target->NowPlayingIndex = target->size;
        *errorFlag = SUCCESS;
        return SUCCESS;
    }
    if(target->NowPlaying == target->Items[0]) {
        target->NowPlaying = NULL;
        target->NowPlayingIndex = NOTPLAYING;
        *errorFlag = SUCCESS;
        return NOTPLAYING;
    }
    target->NowPlaying = target->Items[target->NowPlayingIndex - 1];
    target->NowPlayingIndex -= 1;
    *errorFlag = SUCCESS;
    return SUCCESS;
}

// Lê string sem tamanho definido via stdin
// alocada dinamicamente na memoria
// é carregada para a memória em blocos
// @return Ponteiro para a string alocada dinamicamente
// @param bufferSize tamanho dos blocos de alocação
char* ReadLine(int bufferSize, int* errorFlag) {

    char* String = NULL;
    char  input = 'a';
    int tamanhoString = 0, bufferIndex = 0;
    
    char buffer[bufferSize + 1]; 
    buffer[bufferSize] = '\0';
    memset(buffer, '@', bufferSize);
    
    // loop:
    // lê as letras até achar \n
    // ou até encher o buffer com n caracteres
    // depois realoca a string com o tamanho do
    // bloco lido, passa coloca esse bloco na string
    // e limpa o buffer para a proxima iteração
    do{
        input = fgetc(stdin);
        if(input == '\n' || input == '\r'){
            buffer[bufferIndex] = '\0';
        }
        else {
            buffer[bufferIndex] = input;
        }
        bufferIndex++;

        if(debug) printf("buffer[%d]: %s\n", bufferIndex, buffer);

        if(bufferIndex == bufferSize || input == '\n' || input == '\r') {
            tamanhoString += bufferIndex;
            String = (char*) realloc(String, tamanhoString);
            if(String == NULL) {
                *errorFlag = 1;
                return NULL;
            }
            memcpy(String + tamanhoString - bufferIndex, buffer, bufferIndex);
            if(debug) puts(String);
            bufferIndex = 0;
        }

    } while(input != '\n' && input != '\r');

    // limpa o \n que sobra no stdin
    // caso o formato seja \r\n
    if(input == '\r') {
        getchar();
    }

    *errorFlag = 0;
    return String;
}

// Soma polinomial que interpreta o valor binário como um valor numérico.
// Quanto mais próximo o valor de retorno, mais próximo seu binário está do ideal.
// Não há necessidade de entender o funcionamento dessa função.
//
// Parâmetros: Nome do arquivo (binFilename: char *)
// Retorno: Nada (void)
void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

