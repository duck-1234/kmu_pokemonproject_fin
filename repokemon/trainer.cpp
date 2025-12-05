#include "trainer.h"
#include <string>

// static index 변수 가능 (선택)
static int indexTown1 = 0;
static int indexTown2 = 0;
static int indexTown3 = 0;
static int indexTown4 = 0;

Trainer selectTrainer(int town) {
    Trainer t;
    switch (town) {
    case 1: {
        std::string names[] = { "유체", "강연", "미정", "카렌", "아이리스" };
        std::string pokes[] = { "이상해씨", "파이리", "윈디", "헬가", "갸라도스" };
        int i = indexTown1 % 5;
        indexTown1++;
        t.name = names[i];
        t.pokemon = createPokemon(pokes[i]);  // 단일 포켓몬 할당
        break;
    }
    case 2: {
        std::string names[] = { "호일", "이슬", "철구", "초련", "독수" };
        std::string pokes[] = { "스라크", "별가사리", "리오르", "아쿠스타", "아리아도스" };
        int i = indexTown2 % 5;
        indexTown2++;
        t.name = names[i];
        t.pokemon = createPokemon(pokes[i]);
        break;
    }
    case 3: {
        std::string names[] = { "웅", "강석", "규리", "아크로마", "로즈" };
        std::string pokes[] = { "코코파스", "루카리오", "아쿠스타", "기기기어르", "대왕끼리동" };
        int i = indexTown3 % 5;
        indexTown3++;
        t.name = names[i];
        t.pokemon = createPokemon(pokes[i]);
        break;
    }
    case 4: {
        std::string names[] = { "맥슬러", "전진", "이향", "윤진", "성호" };
        std::string pokes[] = { "플로젤", "렌트라", "킹드라", "밀로틱", "메타그로스" };
        int i = indexTown4 % 5;
        indexTown4++;
        t.name = names[i];
        t.pokemon = createPokemon(pokes[i]);
        break;
    }
    default:
        t.name = "오류";
        t.pokemon = createPokemon("missing.no");
        break;
    }
    return t;
}