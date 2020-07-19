/*62:*/
#line 1489 "dummy.w"

#include "texextern.h"
#include "texdefs.h"
#include "textypes.h"

extern uint8_t*hpos,*hstart,*hend;

static int file_offset= 0;
static int tally= 0;

void print_ln(void)
{putc('\n',hlog);file_offset= 0;
}

void print_char(ASCII_code s)
{putc(s,hlog);file_offset++;tally++;
if(file_offset==max_print_line)print_ln();
}

void print_nl(char*s)
{if(file_offset> 0)print_ln();
print_str(s);
}

void print(int s);

void print_esc(str_number s)
{print_char('\\');
print(s);
}

void print_int(int n)
{int k= fprintf(hlog,"%d",n);
file_offset+= k;tally+= k;
if(file_offset==max_print_line)print_ln();
}

/*:62*//*65:*/
#line 1585 "dummy.w"


/*1841:*/
#line 26903 "dummy.w"

typedef enum{
str_start_256= sizeof(str_0_255)-1,
str_start_257= str_start_256+sizeof(str_256)-1,
str_start_258= str_start_257+sizeof(str_257)-1,
str_start_259= str_start_258+sizeof(str_258)-1,
str_start_260= str_start_259+sizeof(str_259)-1,
str_start_261= str_start_260+sizeof(str_260)-1,
str_start_262= str_start_261+sizeof(str_261)-1,
str_start_263= str_start_262+sizeof(str_262)-1,
str_start_264= str_start_263+sizeof(str_263)-1,
str_start_265= str_start_264+sizeof(str_264)-1,
str_start_266= str_start_265+sizeof(str_265)-1,
str_start_267= str_start_266+sizeof(str_266)-1,
str_start_268= str_start_267+sizeof(str_267)-1,
str_start_269= str_start_268+sizeof(str_268)-1,
str_start_270= str_start_269+sizeof(str_269)-1,
str_start_271= str_start_270+sizeof(str_270)-1,
str_start_272= str_start_271+sizeof(str_271)-1,
str_start_273= str_start_272+sizeof(str_272)-1,
str_start_274= str_start_273+sizeof(str_273)-1,
str_start_275= str_start_274+sizeof(str_274)-1,
str_start_276= str_start_275+sizeof(str_275)-1,
str_start_277= str_start_276+sizeof(str_276)-1,
str_start_278= str_start_277+sizeof(str_277)-1,
str_start_279= str_start_278+sizeof(str_278)-1,
str_start_280= str_start_279+sizeof(str_279)-1,
str_start_281= str_start_280+sizeof(str_280)-1,
str_start_282= str_start_281+sizeof(str_281)-1,
str_start_283= str_start_282+sizeof(str_282)-1,
str_start_284= str_start_283+sizeof(str_283)-1,
str_start_285= str_start_284+sizeof(str_284)-1,
str_start_286= str_start_285+sizeof(str_285)-1,
str_start_287= str_start_286+sizeof(str_286)-1,
str_start_288= str_start_287+sizeof(str_287)-1,
str_start_289= str_start_288+sizeof(str_288)-1,
str_start_290= str_start_289+sizeof(str_289)-1,
str_start_291= str_start_290+sizeof(str_290)-1,
str_start_292= str_start_291+sizeof(str_291)-1,
str_start_293= str_start_292+sizeof(str_292)-1,
str_start_294= str_start_293+sizeof(str_293)-1,
str_start_295= str_start_294+sizeof(str_294)-1,
str_start_296= str_start_295+sizeof(str_295)-1,
str_start_297= str_start_296+sizeof(str_296)-1,
str_start_298= str_start_297+sizeof(str_297)-1,
str_start_299= str_start_298+sizeof(str_298)-1,
str_start_300= str_start_299+sizeof(str_299)-1,
str_start_301= str_start_300+sizeof(str_300)-1,
str_start_302= str_start_301+sizeof(str_301)-1,
str_start_303= str_start_302+sizeof(str_302)-1,
str_start_304= str_start_303+sizeof(str_303)-1,
str_start_305= str_start_304+sizeof(str_304)-1,
str_start_306= str_start_305+sizeof(str_305)-1,
str_start_307= str_start_306+sizeof(str_306)-1,
str_start_308= str_start_307+sizeof(str_307)-1,
str_start_309= str_start_308+sizeof(str_308)-1,
str_start_310= str_start_309+sizeof(str_309)-1,
str_start_311= str_start_310+sizeof(str_310)-1,
str_start_312= str_start_311+sizeof(str_311)-1,
str_start_313= str_start_312+sizeof(str_312)-1,
str_start_314= str_start_313+sizeof(str_313)-1,
str_start_315= str_start_314+sizeof(str_314)-1,
str_start_316= str_start_315+sizeof(str_315)-1,
str_start_317= str_start_316+sizeof(str_316)-1,
str_start_318= str_start_317+sizeof(str_317)-1,
str_start_319= str_start_318+sizeof(str_318)-1,
str_start_320= str_start_319+sizeof(str_319)-1,
str_start_321= str_start_320+sizeof(str_320)-1,
str_start_322= str_start_321+sizeof(str_321)-1,
str_start_323= str_start_322+sizeof(str_322)-1,
str_start_324= str_start_323+sizeof(str_323)-1,
str_start_325= str_start_324+sizeof(str_324)-1,
str_start_326= str_start_325+sizeof(str_325)-1,
str_start_327= str_start_326+sizeof(str_326)-1,
str_start_328= str_start_327+sizeof(str_327)-1,
str_start_329= str_start_328+sizeof(str_328)-1,
str_start_330= str_start_329+sizeof(str_329)-1,
str_start_331= str_start_330+sizeof(str_330)-1,
str_start_332= str_start_331+sizeof(str_331)-1,
str_start_333= str_start_332+sizeof(str_332)-1,
str_start_334= str_start_333+sizeof(str_333)-1,
str_start_335= str_start_334+sizeof(str_334)-1,
str_start_336= str_start_335+sizeof(str_335)-1,
str_start_337= str_start_336+sizeof(str_336)-1,
str_start_338= str_start_337+sizeof(str_337)-1,
str_start_339= str_start_338+sizeof(str_338)-1,
str_start_340= str_start_339+sizeof(str_339)-1,
str_start_341= str_start_340+sizeof(str_340)-1,
str_start_342= str_start_341+sizeof(str_341)-1,
str_start_343= str_start_342+sizeof(str_342)-1,
str_start_344= str_start_343+sizeof(str_343)-1,
str_start_345= str_start_344+sizeof(str_344)-1,
str_start_346= str_start_345+sizeof(str_345)-1,
str_start_347= str_start_346+sizeof(str_346)-1,
str_start_348= str_start_347+sizeof(str_347)-1,
str_start_349= str_start_348+sizeof(str_348)-1,
str_start_350= str_start_349+sizeof(str_349)-1,
str_start_351= str_start_350+sizeof(str_350)-1,
str_start_352= str_start_351+sizeof(str_351)-1,
str_start_353= str_start_352+sizeof(str_352)-1,
str_start_354= str_start_353+sizeof(str_353)-1,
str_start_355= str_start_354+sizeof(str_354)-1,
str_start_356= str_start_355+sizeof(str_355)-1,
str_start_357= str_start_356+sizeof(str_356)-1,
str_start_358= str_start_357+sizeof(str_357)-1,
str_start_359= str_start_358+sizeof(str_358)-1,
str_start_360= str_start_359+sizeof(str_359)-1,
str_start_361= str_start_360+sizeof(str_360)-1,
str_start_362= str_start_361+sizeof(str_361)-1,
str_start_363= str_start_362+sizeof(str_362)-1,
str_start_364= str_start_363+sizeof(str_363)-1,
str_start_365= str_start_364+sizeof(str_364)-1,
str_start_366= str_start_365+sizeof(str_365)-1,
str_start_367= str_start_366+sizeof(str_366)-1,
str_start_368= str_start_367+sizeof(str_367)-1,
str_start_369= str_start_368+sizeof(str_368)-1,
str_start_370= str_start_369+sizeof(str_369)-1,
str_start_371= str_start_370+sizeof(str_370)-1,
str_start_372= str_start_371+sizeof(str_371)-1,
str_start_373= str_start_372+sizeof(str_372)-1,
str_start_374= str_start_373+sizeof(str_373)-1,
str_start_375= str_start_374+sizeof(str_374)-1,
str_start_376= str_start_375+sizeof(str_375)-1,
str_start_377= str_start_376+sizeof(str_376)-1,
str_start_378= str_start_377+sizeof(str_377)-1,
str_start_379= str_start_378+sizeof(str_378)-1,
str_start_380= str_start_379+sizeof(str_379)-1,
str_start_381= str_start_380+sizeof(str_380)-1,
str_start_382= str_start_381+sizeof(str_381)-1,
str_start_383= str_start_382+sizeof(str_382)-1,
str_start_384= str_start_383+sizeof(str_383)-1,
str_start_385= str_start_384+sizeof(str_384)-1,
str_start_386= str_start_385+sizeof(str_385)-1,
str_start_387= str_start_386+sizeof(str_386)-1,
str_start_388= str_start_387+sizeof(str_387)-1,
str_start_389= str_start_388+sizeof(str_388)-1,
str_start_390= str_start_389+sizeof(str_389)-1,
str_start_391= str_start_390+sizeof(str_390)-1,
str_start_392= str_start_391+sizeof(str_391)-1,
str_start_393= str_start_392+sizeof(str_392)-1,
str_start_394= str_start_393+sizeof(str_393)-1,
str_start_395= str_start_394+sizeof(str_394)-1,
str_start_396= str_start_395+sizeof(str_395)-1,
str_start_397= str_start_396+sizeof(str_396)-1,
str_start_398= str_start_397+sizeof(str_397)-1,
str_start_399= str_start_398+sizeof(str_398)-1,
str_start_400= str_start_399+sizeof(str_399)-1,
str_start_401= str_start_400+sizeof(str_400)-1,
str_start_402= str_start_401+sizeof(str_401)-1,
str_start_403= str_start_402+sizeof(str_402)-1,
str_start_404= str_start_403+sizeof(str_403)-1,
str_start_405= str_start_404+sizeof(str_404)-1,
str_start_406= str_start_405+sizeof(str_405)-1,
str_start_407= str_start_406+sizeof(str_406)-1,
str_start_408= str_start_407+sizeof(str_407)-1,
str_start_409= str_start_408+sizeof(str_408)-1,
str_start_410= str_start_409+sizeof(str_409)-1,
str_start_411= str_start_410+sizeof(str_410)-1,
str_start_412= str_start_411+sizeof(str_411)-1,
str_start_413= str_start_412+sizeof(str_412)-1,
str_start_414= str_start_413+sizeof(str_413)-1,
str_start_415= str_start_414+sizeof(str_414)-1,
str_start_416= str_start_415+sizeof(str_415)-1,
str_start_417= str_start_416+sizeof(str_416)-1,
str_start_418= str_start_417+sizeof(str_417)-1,
str_start_419= str_start_418+sizeof(str_418)-1,
str_start_420= str_start_419+sizeof(str_419)-1,
str_start_421= str_start_420+sizeof(str_420)-1,
str_start_422= str_start_421+sizeof(str_421)-1,
str_start_423= str_start_422+sizeof(str_422)-1,
str_start_424= str_start_423+sizeof(str_423)-1,
str_start_425= str_start_424+sizeof(str_424)-1,
str_start_426= str_start_425+sizeof(str_425)-1,
str_start_427= str_start_426+sizeof(str_426)-1,
str_start_428= str_start_427+sizeof(str_427)-1,
str_start_429= str_start_428+sizeof(str_428)-1,
str_start_430= str_start_429+sizeof(str_429)-1,
str_start_431= str_start_430+sizeof(str_430)-1,
str_start_432= str_start_431+sizeof(str_431)-1,
str_start_433= str_start_432+sizeof(str_432)-1,
str_start_434= str_start_433+sizeof(str_433)-1,
str_start_435= str_start_434+sizeof(str_434)-1,
str_start_436= str_start_435+sizeof(str_435)-1,
str_start_437= str_start_436+sizeof(str_436)-1,
str_start_438= str_start_437+sizeof(str_437)-1,
str_start_439= str_start_438+sizeof(str_438)-1,
str_start_440= str_start_439+sizeof(str_439)-1,
str_start_441= str_start_440+sizeof(str_440)-1,
str_start_442= str_start_441+sizeof(str_441)-1,
str_start_443= str_start_442+sizeof(str_442)-1,
str_start_444= str_start_443+sizeof(str_443)-1,
str_start_445= str_start_444+sizeof(str_444)-1,
str_start_446= str_start_445+sizeof(str_445)-1,
str_start_447= str_start_446+sizeof(str_446)-1,
str_start_448= str_start_447+sizeof(str_447)-1,
str_start_449= str_start_448+sizeof(str_448)-1,
str_start_450= str_start_449+sizeof(str_449)-1,
str_start_451= str_start_450+sizeof(str_450)-1,
str_start_452= str_start_451+sizeof(str_451)-1,
str_start_453= str_start_452+sizeof(str_452)-1,
str_start_454= str_start_453+sizeof(str_453)-1,
str_start_455= str_start_454+sizeof(str_454)-1,
str_start_456= str_start_455+sizeof(str_455)-1,
str_start_457= str_start_456+sizeof(str_456)-1,
str_start_458= str_start_457+sizeof(str_457)-1,
str_start_459= str_start_458+sizeof(str_458)-1,
str_start_460= str_start_459+sizeof(str_459)-1,
str_start_461= str_start_460+sizeof(str_460)-1,
str_start_462= str_start_461+sizeof(str_461)-1,
str_start_463= str_start_462+sizeof(str_462)-1,
str_start_464= str_start_463+sizeof(str_463)-1,
str_start_465= str_start_464+sizeof(str_464)-1,
str_start_466= str_start_465+sizeof(str_465)-1,
str_start_467= str_start_466+sizeof(str_466)-1,
str_start_468= str_start_467+sizeof(str_467)-1,
str_start_469= str_start_468+sizeof(str_468)-1,
str_start_470= str_start_469+sizeof(str_469)-1,
str_start_471= str_start_470+sizeof(str_470)-1,
str_start_472= str_start_471+sizeof(str_471)-1,
str_start_473= str_start_472+sizeof(str_472)-1,
str_start_474= str_start_473+sizeof(str_473)-1,
str_start_475= str_start_474+sizeof(str_474)-1,
str_start_476= str_start_475+sizeof(str_475)-1,
str_start_477= str_start_476+sizeof(str_476)-1,
str_start_478= str_start_477+sizeof(str_477)-1,
str_start_479= str_start_478+sizeof(str_478)-1,
str_start_480= str_start_479+sizeof(str_479)-1,
str_start_481= str_start_480+sizeof(str_480)-1,
str_start_482= str_start_481+sizeof(str_481)-1,
str_start_483= str_start_482+sizeof(str_482)-1,
str_start_484= str_start_483+sizeof(str_483)-1,
str_start_485= str_start_484+sizeof(str_484)-1,
str_start_486= str_start_485+sizeof(str_485)-1,
str_start_487= str_start_486+sizeof(str_486)-1,
str_start_488= str_start_487+sizeof(str_487)-1,
str_start_489= str_start_488+sizeof(str_488)-1,
str_start_490= str_start_489+sizeof(str_489)-1,
str_start_491= str_start_490+sizeof(str_490)-1,
str_start_492= str_start_491+sizeof(str_491)-1,
str_start_493= str_start_492+sizeof(str_492)-1,
str_start_494= str_start_493+sizeof(str_493)-1,
str_start_495= str_start_494+sizeof(str_494)-1,
str_start_496= str_start_495+sizeof(str_495)-1,
str_start_497= str_start_496+sizeof(str_496)-1,
str_start_498= str_start_497+sizeof(str_497)-1,
str_start_499= str_start_498+sizeof(str_498)-1,
str_start_500= str_start_499+sizeof(str_499)-1,
str_start_501= str_start_500+sizeof(str_500)-1,
str_start_502= str_start_501+sizeof(str_501)-1,
str_start_503= str_start_502+sizeof(str_502)-1,
str_start_504= str_start_503+sizeof(str_503)-1,
str_start_505= str_start_504+sizeof(str_504)-1,
str_start_506= str_start_505+sizeof(str_505)-1,
str_start_507= str_start_506+sizeof(str_506)-1,
str_start_508= str_start_507+sizeof(str_507)-1,
str_start_509= str_start_508+sizeof(str_508)-1,
str_start_510= str_start_509+sizeof(str_509)-1,
str_start_511= str_start_510+sizeof(str_510)-1,
str_start_512= str_start_511+sizeof(str_511)-1,
str_start_513= str_start_512+sizeof(str_512)-1,
str_start_514= str_start_513+sizeof(str_513)-1,
str_start_515= str_start_514+sizeof(str_514)-1,
str_start_516= str_start_515+sizeof(str_515)-1,
str_start_517= str_start_516+sizeof(str_516)-1,
str_start_518= str_start_517+sizeof(str_517)-1,
str_start_519= str_start_518+sizeof(str_518)-1,
str_start_520= str_start_519+sizeof(str_519)-1,
str_start_521= str_start_520+sizeof(str_520)-1,
str_start_522= str_start_521+sizeof(str_521)-1,
str_start_523= str_start_522+sizeof(str_522)-1,
str_start_524= str_start_523+sizeof(str_523)-1,
str_start_525= str_start_524+sizeof(str_524)-1,
str_start_526= str_start_525+sizeof(str_525)-1,
str_start_527= str_start_526+sizeof(str_526)-1,
str_start_528= str_start_527+sizeof(str_527)-1,
str_start_529= str_start_528+sizeof(str_528)-1,
str_start_530= str_start_529+sizeof(str_529)-1,
str_start_531= str_start_530+sizeof(str_530)-1,
str_start_532= str_start_531+sizeof(str_531)-1,
str_start_533= str_start_532+sizeof(str_532)-1,
str_start_534= str_start_533+sizeof(str_533)-1,
str_start_535= str_start_534+sizeof(str_534)-1,
str_start_536= str_start_535+sizeof(str_535)-1,
str_start_537= str_start_536+sizeof(str_536)-1,
str_start_538= str_start_537+sizeof(str_537)-1,
str_start_539= str_start_538+sizeof(str_538)-1,
str_start_540= str_start_539+sizeof(str_539)-1,
str_start_541= str_start_540+sizeof(str_540)-1,
str_start_542= str_start_541+sizeof(str_541)-1,
str_start_543= str_start_542+sizeof(str_542)-1,
str_start_544= str_start_543+sizeof(str_543)-1,
str_start_545= str_start_544+sizeof(str_544)-1,
str_start_546= str_start_545+sizeof(str_545)-1,
str_start_547= str_start_546+sizeof(str_546)-1,
str_start_548= str_start_547+sizeof(str_547)-1,
str_start_549= str_start_548+sizeof(str_548)-1,
str_start_550= str_start_549+sizeof(str_549)-1,
str_start_551= str_start_550+sizeof(str_550)-1,
str_start_552= str_start_551+sizeof(str_551)-1,
str_start_553= str_start_552+sizeof(str_552)-1,
str_start_554= str_start_553+sizeof(str_553)-1,
str_start_555= str_start_554+sizeof(str_554)-1,
str_start_556= str_start_555+sizeof(str_555)-1,
str_start_557= str_start_556+sizeof(str_556)-1,
str_start_558= str_start_557+sizeof(str_557)-1,
str_start_559= str_start_558+sizeof(str_558)-1,
str_start_560= str_start_559+sizeof(str_559)-1,
str_start_561= str_start_560+sizeof(str_560)-1,
str_start_562= str_start_561+sizeof(str_561)-1,
str_start_563= str_start_562+sizeof(str_562)-1,
str_start_564= str_start_563+sizeof(str_563)-1,
str_start_565= str_start_564+sizeof(str_564)-1,
str_start_566= str_start_565+sizeof(str_565)-1,
str_start_567= str_start_566+sizeof(str_566)-1,
str_start_568= str_start_567+sizeof(str_567)-1,
str_start_569= str_start_568+sizeof(str_568)-1,
str_start_570= str_start_569+sizeof(str_569)-1,
str_start_571= str_start_570+sizeof(str_570)-1,
str_start_572= str_start_571+sizeof(str_571)-1,
str_start_573= str_start_572+sizeof(str_572)-1,
str_start_574= str_start_573+sizeof(str_573)-1,
str_start_575= str_start_574+sizeof(str_574)-1,
str_start_576= str_start_575+sizeof(str_575)-1,
str_start_577= str_start_576+sizeof(str_576)-1,
str_start_578= str_start_577+sizeof(str_577)-1,
str_start_579= str_start_578+sizeof(str_578)-1,
str_start_580= str_start_579+sizeof(str_579)-1,
str_start_581= str_start_580+sizeof(str_580)-1,
str_start_582= str_start_581+sizeof(str_581)-1,
str_start_583= str_start_582+sizeof(str_582)-1,
str_start_584= str_start_583+sizeof(str_583)-1,
str_start_585= str_start_584+sizeof(str_584)-1,
str_start_586= str_start_585+sizeof(str_585)-1,
str_start_587= str_start_586+sizeof(str_586)-1,
str_start_588= str_start_587+sizeof(str_587)-1,
str_start_589= str_start_588+sizeof(str_588)-1,
str_start_590= str_start_589+sizeof(str_589)-1,
str_start_591= str_start_590+sizeof(str_590)-1,
str_start_592= str_start_591+sizeof(str_591)-1,
str_start_593= str_start_592+sizeof(str_592)-1,
str_start_594= str_start_593+sizeof(str_593)-1,
str_start_595= str_start_594+sizeof(str_594)-1,
str_start_596= str_start_595+sizeof(str_595)-1,
str_start_597= str_start_596+sizeof(str_596)-1,
str_start_598= str_start_597+sizeof(str_597)-1,
str_start_599= str_start_598+sizeof(str_598)-1,
str_start_600= str_start_599+sizeof(str_599)-1,
str_start_601= str_start_600+sizeof(str_600)-1,
str_start_602= str_start_601+sizeof(str_601)-1,
str_start_603= str_start_602+sizeof(str_602)-1,
str_start_604= str_start_603+sizeof(str_603)-1,
str_start_605= str_start_604+sizeof(str_604)-1,
str_start_606= str_start_605+sizeof(str_605)-1,
str_start_607= str_start_606+sizeof(str_606)-1,
str_start_608= str_start_607+sizeof(str_607)-1,
str_start_609= str_start_608+sizeof(str_608)-1,
str_start_610= str_start_609+sizeof(str_609)-1,
str_start_611= str_start_610+sizeof(str_610)-1,
str_start_612= str_start_611+sizeof(str_611)-1,
str_start_613= str_start_612+sizeof(str_612)-1,
str_start_614= str_start_613+sizeof(str_613)-1,
str_start_615= str_start_614+sizeof(str_614)-1,
str_start_616= str_start_615+sizeof(str_615)-1,
str_start_617= str_start_616+sizeof(str_616)-1,
str_start_618= str_start_617+sizeof(str_617)-1,
str_start_619= str_start_618+sizeof(str_618)-1,
str_start_620= str_start_619+sizeof(str_619)-1,
str_start_621= str_start_620+sizeof(str_620)-1,
str_start_622= str_start_621+sizeof(str_621)-1,
str_start_623= str_start_622+sizeof(str_622)-1,
str_start_624= str_start_623+sizeof(str_623)-1,
str_start_625= str_start_624+sizeof(str_624)-1,
str_start_626= str_start_625+sizeof(str_625)-1,
str_start_627= str_start_626+sizeof(str_626)-1,
str_start_628= str_start_627+sizeof(str_627)-1,
str_start_629= str_start_628+sizeof(str_628)-1,
str_start_630= str_start_629+sizeof(str_629)-1,
str_start_631= str_start_630+sizeof(str_630)-1,
str_start_632= str_start_631+sizeof(str_631)-1,
str_start_633= str_start_632+sizeof(str_632)-1,
str_start_634= str_start_633+sizeof(str_633)-1,
str_start_635= str_start_634+sizeof(str_634)-1,
str_start_636= str_start_635+sizeof(str_635)-1,
str_start_637= str_start_636+sizeof(str_636)-1,
str_start_638= str_start_637+sizeof(str_637)-1,
str_start_639= str_start_638+sizeof(str_638)-1,
str_start_640= str_start_639+sizeof(str_639)-1,
str_start_641= str_start_640+sizeof(str_640)-1,
str_start_642= str_start_641+sizeof(str_641)-1,
str_start_643= str_start_642+sizeof(str_642)-1,
str_start_644= str_start_643+sizeof(str_643)-1,
str_start_645= str_start_644+sizeof(str_644)-1,
str_start_646= str_start_645+sizeof(str_645)-1,
str_start_647= str_start_646+sizeof(str_646)-1,
str_start_648= str_start_647+sizeof(str_647)-1,
str_start_649= str_start_648+sizeof(str_648)-1,
str_start_650= str_start_649+sizeof(str_649)-1,
str_start_651= str_start_650+sizeof(str_650)-1,
str_start_652= str_start_651+sizeof(str_651)-1,
str_start_653= str_start_652+sizeof(str_652)-1,
str_start_654= str_start_653+sizeof(str_653)-1,
str_start_655= str_start_654+sizeof(str_654)-1,
str_start_656= str_start_655+sizeof(str_655)-1,
str_start_657= str_start_656+sizeof(str_656)-1,
str_start_658= str_start_657+sizeof(str_657)-1,
str_start_659= str_start_658+sizeof(str_658)-1,
str_start_660= str_start_659+sizeof(str_659)-1,
str_start_661= str_start_660+sizeof(str_660)-1,
str_start_662= str_start_661+sizeof(str_661)-1,
str_start_663= str_start_662+sizeof(str_662)-1,
str_start_664= str_start_663+sizeof(str_663)-1,
str_start_665= str_start_664+sizeof(str_664)-1,
str_start_666= str_start_665+sizeof(str_665)-1,
str_start_667= str_start_666+sizeof(str_666)-1,
str_start_668= str_start_667+sizeof(str_667)-1,
str_start_end}str_starts;

/*:1841*/
#line 1587 "dummy.w"

packed_ASCII_code str_pool[]= /*1839:*/
#line 26740 "dummy.w"

str_0_255
str_256 str_257 str_258 str_259 str_260 str_261 str_262 str_263
str_264 str_265 str_266 str_267 str_268 str_269 str_270 str_271
str_272 str_273 str_274 str_275 str_276 str_277 str_278 str_279
str_280 str_281 str_282 str_283 str_284 str_285 str_286 str_287
str_288 str_289 str_290 str_291 str_292 str_293 str_294 str_295
str_296 str_297 str_298 str_299 str_300 str_301 str_302 str_303
str_304 str_305 str_306 str_307 str_308 str_309 str_310 str_311
str_312 str_313 str_314 str_315 str_316 str_317 str_318 str_319
str_320 str_321 str_322 str_323 str_324 str_325 str_326 str_327
str_328 str_329 str_330 str_331 str_332 str_333 str_334 str_335
str_336 str_337 str_338 str_339 str_340 str_341 str_342 str_343
str_344 str_345 str_346 str_347 str_348 str_349 str_350 str_351
str_352 str_353 str_354 str_355 str_356 str_357 str_358 str_359
str_360 str_361 str_362 str_363 str_364 str_365 str_366 str_367
str_368 str_369 str_370 str_371 str_372 str_373 str_374 str_375
str_376 str_377 str_378 str_379 str_380 str_381 str_382 str_383
str_384 str_385 str_386 str_387 str_388 str_389 str_390 str_391
str_392 str_393 str_394 str_395 str_396 str_397 str_398 str_399
str_400 str_401 str_402 str_403 str_404 str_405 str_406 str_407
str_408 str_409 str_410 str_411 str_412 str_413 str_414 str_415
str_416 str_417 str_418 str_419 str_420 str_421 str_422 str_423
str_424 str_425 str_426 str_427 str_428 str_429 str_430 str_431
str_432 str_433 str_434 str_435 str_436 str_437 str_438 str_439
str_440 str_441 str_442 str_443 str_444 str_445 str_446 str_447
str_448 str_449 str_450 str_451 str_452 str_453 str_454 str_455
str_456 str_457 str_458 str_459 str_460 str_461 str_462 str_463
str_464 str_465 str_466 str_467 str_468 str_469 str_470 str_471
str_472 str_473 str_474 str_475 str_476 str_477 str_478 str_479
str_480 str_481 str_482 str_483 str_484 str_485 str_486 str_487
str_488 str_489 str_490 str_491 str_492 str_493 str_494 str_495
str_496 str_497 str_498 str_499 str_500 str_501 str_502 str_503
str_504 str_505 str_506 str_507 str_508 str_509 str_510 str_511
str_512 str_513 str_514 str_515 str_516 str_517 str_518 str_519
str_520 str_521 str_522 str_523 str_524 str_525 str_526 str_527
str_528 str_529 str_530 str_531 str_532 str_533 str_534 str_535
str_536 str_537 str_538 str_539 str_540 str_541 str_542 str_543
str_544 str_545 str_546 str_547 str_548 str_549 str_550 str_551
str_552 str_553 str_554 str_555 str_556 str_557 str_558 str_559
str_560 str_561 str_562 str_563 str_564 str_565 str_566 str_567
str_568 str_569 str_570 str_571 str_572 str_573 str_574 str_575
str_576 str_577 str_578 str_579 str_580 str_581 str_582 str_583
str_584 str_585 str_586 str_587 str_588 str_589 str_590 str_591
str_592 str_593 str_594 str_595 str_596 str_597 str_598 str_599
str_600 str_601 str_602 str_603 str_604 str_605 str_606 str_607
str_608 str_609 str_610 str_611 str_612 str_613 str_614 str_615
str_616 str_617 str_618 str_619 str_620 str_621 str_622 str_623
str_624 str_625 str_626 str_627 str_628 str_629 str_630 str_631
str_632 str_633 str_634 str_635 str_636 str_637 str_638 str_639
str_640 str_641 str_642 str_643 str_644 str_645 str_646 str_647
str_648 str_649 str_650 str_651 str_652 str_653 str_654 str_655
str_656 str_657 str_658 str_659 str_660 str_661 str_662 str_663
str_664 str_665 str_666 str_667

/*:1839*/
#line 1588 "dummy.w"
;
pool_pointer str_start[]= {/*1840:*/
#line 26795 "dummy.w"

str_start_0_255
str_start_256,str_start_257,str_start_258,str_start_259,
str_start_260,str_start_261,str_start_262,str_start_263,
str_start_264,str_start_265,str_start_266,str_start_267,
str_start_268,str_start_269,str_start_270,str_start_271,
str_start_272,str_start_273,str_start_274,str_start_275,
str_start_276,str_start_277,str_start_278,str_start_279,
str_start_280,str_start_281,str_start_282,str_start_283,
str_start_284,str_start_285,str_start_286,str_start_287,
str_start_288,str_start_289,str_start_290,str_start_291,
str_start_292,str_start_293,str_start_294,str_start_295,
str_start_296,str_start_297,str_start_298,str_start_299,
str_start_300,str_start_301,str_start_302,str_start_303,
str_start_304,str_start_305,str_start_306,str_start_307,
str_start_308,str_start_309,str_start_310,str_start_311,
str_start_312,str_start_313,str_start_314,str_start_315,
str_start_316,str_start_317,str_start_318,str_start_319,
str_start_320,str_start_321,str_start_322,str_start_323,
str_start_324,str_start_325,str_start_326,str_start_327,
str_start_328,str_start_329,str_start_330,str_start_331,
str_start_332,str_start_333,str_start_334,str_start_335,
str_start_336,str_start_337,str_start_338,str_start_339,
str_start_340,str_start_341,str_start_342,str_start_343,
str_start_344,str_start_345,str_start_346,str_start_347,
str_start_348,str_start_349,str_start_350,str_start_351,
str_start_352,str_start_353,str_start_354,str_start_355,
str_start_356,str_start_357,str_start_358,str_start_359,
str_start_360,str_start_361,str_start_362,str_start_363,
str_start_364,str_start_365,str_start_366,str_start_367,
str_start_368,str_start_369,str_start_370,str_start_371,
str_start_372,str_start_373,str_start_374,str_start_375,
str_start_376,str_start_377,str_start_378,str_start_379,
str_start_380,str_start_381,str_start_382,str_start_383,
str_start_384,str_start_385,str_start_386,str_start_387,
str_start_388,str_start_389,str_start_390,str_start_391,
str_start_392,str_start_393,str_start_394,str_start_395,
str_start_396,str_start_397,str_start_398,str_start_399,
str_start_400,str_start_401,str_start_402,str_start_403,
str_start_404,str_start_405,str_start_406,str_start_407,
str_start_408,str_start_409,str_start_410,str_start_411,
str_start_412,str_start_413,str_start_414,str_start_415,
str_start_416,str_start_417,str_start_418,str_start_419,
str_start_420,str_start_421,str_start_422,str_start_423,
str_start_424,str_start_425,str_start_426,str_start_427,
str_start_428,str_start_429,str_start_430,str_start_431,
str_start_432,str_start_433,str_start_434,str_start_435,
str_start_436,str_start_437,str_start_438,str_start_439,
str_start_440,str_start_441,str_start_442,str_start_443,
str_start_444,str_start_445,str_start_446,str_start_447,
str_start_448,str_start_449,str_start_450,str_start_451,
str_start_452,str_start_453,str_start_454,str_start_455,
str_start_456,str_start_457,str_start_458,str_start_459,
str_start_460,str_start_461,str_start_462,str_start_463,
str_start_464,str_start_465,str_start_466,str_start_467,
str_start_468,str_start_469,str_start_470,str_start_471,
str_start_472,str_start_473,str_start_474,str_start_475,
str_start_476,str_start_477,str_start_478,str_start_479,
str_start_480,str_start_481,str_start_482,str_start_483,
str_start_484,str_start_485,str_start_486,str_start_487,
str_start_488,str_start_489,str_start_490,str_start_491,
str_start_492,str_start_493,str_start_494,str_start_495,
str_start_496,str_start_497,str_start_498,str_start_499,
str_start_500,str_start_501,str_start_502,str_start_503,
str_start_504,str_start_505,str_start_506,str_start_507,
str_start_508,str_start_509,str_start_510,str_start_511,
str_start_512,str_start_513,str_start_514,str_start_515,
str_start_516,str_start_517,str_start_518,str_start_519,
str_start_520,str_start_521,str_start_522,str_start_523,
str_start_524,str_start_525,str_start_526,str_start_527,
str_start_528,str_start_529,str_start_530,str_start_531,
str_start_532,str_start_533,str_start_534,str_start_535,
str_start_536,str_start_537,str_start_538,str_start_539,
str_start_540,str_start_541,str_start_542,str_start_543,
str_start_544,str_start_545,str_start_546,str_start_547,
str_start_548,str_start_549,str_start_550,str_start_551,
str_start_552,str_start_553,str_start_554,str_start_555,
str_start_556,str_start_557,str_start_558,str_start_559,
str_start_560,str_start_561,str_start_562,str_start_563,
str_start_564,str_start_565,str_start_566,str_start_567,
str_start_568,str_start_569,str_start_570,str_start_571,
str_start_572,str_start_573,str_start_574,str_start_575,
str_start_576,str_start_577,str_start_578,str_start_579,
str_start_580,str_start_581,str_start_582,str_start_583,
str_start_584,str_start_585,str_start_586,str_start_587,
str_start_588,str_start_589,str_start_590,str_start_591,
str_start_592,str_start_593,str_start_594,str_start_595,
str_start_596,str_start_597,str_start_598,str_start_599,
str_start_600,str_start_601,str_start_602,str_start_603,
str_start_604,str_start_605,str_start_606,str_start_607,
str_start_608,str_start_609,str_start_610,str_start_611,
str_start_612,str_start_613,str_start_614,str_start_615,
str_start_616,str_start_617,str_start_618,str_start_619,
str_start_620,str_start_621,str_start_622,str_start_623,
str_start_624,str_start_625,str_start_626,str_start_627,
str_start_628,str_start_629,str_start_630,str_start_631,
str_start_632,str_start_633,str_start_634,str_start_635,
str_start_636,str_start_637,str_start_638,str_start_639,
str_start_640,str_start_641,str_start_642,str_start_643,
str_start_644,str_start_645,str_start_646,str_start_647,
str_start_648,str_start_649,str_start_650,str_start_651,
str_start_652,str_start_653,str_start_654,str_start_655,
str_start_656,str_start_657,str_start_658,str_start_659,
str_start_660,str_start_661,str_start_662,str_start_663,
str_start_664,str_start_665,str_start_666,str_start_667,
str_start_668

/*:1840*/
#line 1589 "dummy.w"
};
pool_pointer pool_ptr= /*1842:*/
#line 27320 "dummy.w"
str_start_668

/*:1842*/
#line 1590 "dummy.w"
;
str_number str_ptr= /*1843:*/
#line 27322 "dummy.w"
668

/*:1843*/
#line 1591 "dummy.w"
;
pool_pointer init_pool_ptr;
str_number init_str_ptr;

unsigned int depth_threshold= 200;
int breadth_max= 200;

void print(int s)
{
pool_pointer j;
if(s>=str_ptr||s<0)s= /*1427:*/
#line 25504 "dummy.w"
256
/*:1427*/
#line 1601 "dummy.w"
;
for(j= str_start[s];j<str_start[s+1];j++)print_char(str_pool[j]);
}

void print_str(char*s)
{while(*s!=0)print_char(*s++);
}

/*:65*//*76:*/
#line 1749 "dummy.w"

void print_current_string(void)
{pool_pointer j;
j= str_start[str_ptr];
while(j<pool_ptr)
{print_char(so(str_pool[j]));incr(j);
}
}

/*:76*//*101:*/
#line 2132 "dummy.w"

void overflow(char*s,int n)
{QUIT("Capacity exceeded, sorry [%s=%d=0x%X]\n",s,n,n);
}

/*:101*//*103:*/
#line 2146 "dummy.w"

void confusion(str_number s)

{QUIT("This can't happen(%.*s)",length(s),str_pool+str_start[s]);}

/*:103*//*108:*/
#line 2213 "dummy.w"


int half(int x)
{if(odd(x))return(x+1)/2;
else return x/2;
}

/*:108*//*112:*/
#line 2258 "dummy.w"

void print_scaled(scaled s)

{scaled delta;
if(s<0)
{print_char('-');negate(s);
}
print_int(s/unity);
print_char('.');
s= 10*(s%unity)+5;delta= 10;
do{if(delta> unity)s= s+0100000-50000;
print_char('0'+(s/unity));s= 10*(s%unity);delta= delta*10;
}while(!(s<=delta));
}

/*:112*//*114:*/
#line 2299 "dummy.w"

bool arith_error;
scaled rem;

/*:114*//*116:*/
#line 2323 "dummy.w"

scaled x_over_n(scaled x,int n)
{bool negative;
scaled x_over_n;negative= false;
if(n==0)
{arith_error= true;x_over_n= 0;rem= x;
}
else{if(n<0)
{negate(x);negate(n);negative= true;
}
if(x>=0)
{x_over_n= x/n;rem= x%n;
}
else{x_over_n= -((-x)/n);rem= -((-x)%n);
}
}
if(negative)negate(rem);
return x_over_n;}

/*:116*//*117:*/
#line 2349 "dummy.w"

scaled xn_over_d(scaled x,int n,int d)
{bool positive;
nonnegative_integer t,u,v;
scaled xn_over_d;if(x>=0)positive= true;
else{negate(x);positive= false;
}
t= (x%0100000)*n;
u= (x/0100000)*n+(t/0100000);
v= (u%d)*0100000+(t%0100000);
if(u/d>=0100000)arith_error= true;
else u= 0100000*(u/d)+(v/d);
if(positive)
{xn_over_d= u;rem= v%d;
}
else{xn_over_d= -u;rem= -(v%d);
}
return xn_over_d;}

/*:117*//*118:*/
#line 2388 "dummy.w"

halfword badness(scaled t,scaled s)
{int r;

if(t==0)return 0;
else if(s<=0)return inf_bad;
else{if(t<=7230584)r= (t*297)/s;
else if(s>=1663497)r= t/(s/297);
else r= t;
if(r> 1290)return inf_bad;
else return(r*r*r+0400000)/01000000;
}
}

/*:118*//*133:*/
#line 2684 "dummy.w"
pointer get_avail(void)
{pointer p;
p= avail;
if(p!=null)avail= link(avail);
else{decr(hi_mem_min);p= hi_mem_min;
if(hi_mem_min<=lo_mem_max)
{
overflow("main memory size",mem_max+1-mem_min);


}
}
link(p)= null;
incr_dyn_used;
return p;
}

/*:133*//*136:*/
#line 2727 "dummy.w"

/*127:*/
#line 2595 "dummy.w"

pointer temp_ptr;

/*:127*//*128:*/
#line 2627 "dummy.w"

memory_word mem0[mem_max-mem_min+1],*const mem= mem0-mem_min;
pointer lo_mem_max;
pointer hi_mem_min;

/*:128*//*129:*/
#line 2640 "dummy.w"

int var_used,dyn_used;
/*:129*//*131:*/
#line 2665 "dummy.w"

pointer avail;

/*:131*//*137:*/
#line 2762 "dummy.w"

static pointer rover;

/*:137*/
#line 2728 "dummy.w"

void flush_list(pointer p)
{pointer q,r;
if(p!=null)
{r= p;
do{q= r;r= link(r);
decr_dyn_used;
}while(!(r==null));
link(q)= avail;avail= p;
}
}

/*:136*//*138:*/
#line 2773 "dummy.w"
pointer get_node(int s)
{
pointer p;
pointer q;
int r;
int t;
restart:p= rover;
do{/*140:*/
#line 2824 "dummy.w"

q= p+node_size(p);

while(is_empty(q))
{t= rlink(q);
if(q==rover)rover= t;
llink(t)= llink(q);rlink(llink(q))= t;
q= q+node_size(q);
}
r= q-s;
if(r> p+1)/*141:*/
#line 2839 "dummy.w"

{node_size(p)= r-p;

rover= p;
goto found;
}

/*:141*/
#line 2834 "dummy.w"
;
if(r==p)if(rlink(p)!=p)
/*142:*/
#line 2848 "dummy.w"

{rover= rlink(p);t= llink(p);
llink(rover)= t;rlink(t)= rover;
goto found;
}

/*:142*/
#line 2836 "dummy.w"
;
node_size(p)= q-p

/*:140*/
#line 2781 "dummy.w"
;

p= rlink(p);
}while(!(p==rover));
if(s==010000000000)
{return max_halfword;
}
if(lo_mem_max+2<hi_mem_min)if(lo_mem_max+2<=mem_bot+max_halfword)
/*139:*/
#line 2809 "dummy.w"

{if(hi_mem_min-lo_mem_max>=1998)t= lo_mem_max+1000;
else t= lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;

p= llink(rover);q= lo_mem_max;rlink(p)= q;llink(rover)= q;
if(t> mem_bot+max_halfword)t= mem_bot+max_halfword;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;node_size(q)= t-lo_mem_max;
lo_mem_max= t;link(lo_mem_max)= null;info(lo_mem_max)= null;
rover= q;goto restart;
}

/*:139*/
#line 2789 "dummy.w"
;
overflow("main memory size",mem_max+1-mem_min);


found:link(r)= null;
#ifdef STAT
var_used= var_used+s;
#endif

leak_in(r,s);
return r;
}

/*:138*//*143:*/
#line 2859 "dummy.w"

void free_node(pointer p,halfword s)

{pointer q;
leak_out(p,s);
store_map(p,0,0);
node_size(p)= s;link(p)= empty_flag;
q= llink(rover);llink(p)= q;rlink(p)= rover;
llink(rover)= p;rlink(q)= p;
#ifdef STAT
var_used= var_used-s;
#endif

}

/*:143*//*149:*/
#line 3010 "dummy.w"

pointer new_null_box(void)
{pointer p;
p= get_node(box_node_size);type(p)= hlist_node;
subtype(p)= min_quarterword;
width(p)= 0;depth(p)= 0;height(p)= 0;shift_amount(p)= 0;list_ptr(p)= null;
glue_sign(p)= normal;glue_order(p)= normal;set_glue_ratio_zero(glue_set(p));
return p;
}

/*:149*//*152:*/
#line 3041 "dummy.w"
pointer new_rule(void)
{pointer p;
p= get_node(rule_node_size);type(p)= rule_node;
subtype(p)= 0;
width(p)= null_flag;depth(p)= null_flag;height(p)= null_flag;
return p;
}

/*:152*//*157:*/
#line 3110 "dummy.w"

pointer new_ligature(quarterword f,quarterword c,pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= ligature_node;
font(lig_char(p))= f;character(lig_char(p))= c;lig_ptr(p)= q;
subtype(p)= 0;return p;
}

pointer new_lig_item(quarterword c)
{pointer p;
p= get_node(small_node_size);character(p)= c;lig_ptr(p)= null;
return p;
}

/*:157*//*158:*/
#line 3149 "dummy.w"
pointer new_disc(void)
{pointer p;
p= get_node(small_node_size);type(p)= disc_node;
subtype(p)= 0;pre_break(p)= null;post_break(p)= null;
return p;
}

/*:158*//*160:*/
#line 3183 "dummy.w"
pointer new_math(scaled w,small_number s)
{pointer p;
p= get_node(small_node_size);type(p)= math_node;
subtype(p)= s;width(p)= w;return p;
}

/*:160*//*164:*/
#line 3265 "dummy.w"
pointer new_spec(pointer p)
{pointer q;
q= get_node(glue_spec_size);
mem[q]= mem[p];glue_ref_count(q)= null;
width(q)= width(p);stretch(q)= stretch(p);shrink(q)= shrink(p);
return q;
}

/*:164*//*166:*/
#line 3291 "dummy.w"
pointer new_glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:166*//*169:*/
#line 3329 "dummy.w"
pointer new_kern(scaled w)
{pointer p;
p= get_node(small_node_size);type(p)= kern_node;
subtype(p)= normal;
width(p)= w;
return p;
}

/*:169*//*171:*/
#line 3352 "dummy.w"
pointer new_penalty(int m)
{pointer p;
p= get_node(small_node_size);type(p)= penalty_node;
subtype(p)= 0;
penalty(p)= m;return p;
}

/*:171*//*177:*/
#line 3431 "dummy.w"

void mem_init(void)
{int k;
/*178:*/
#line 3437 "dummy.w"

for(k= mem_bot+1;k<=lo_mem_stat_max;k++)mem[k].sc= 0;


k= mem_bot;while(k<=lo_mem_stat_max)

{glue_ref_count(k)= null+1;
stretch_order(k)= normal;shrink_order(k)= normal;
k= k+glue_spec_size;
}
rover= lo_mem_stat_max+1;
link(rover)= empty_flag;
node_size(rover)= 1000;
llink(rover)= rover;rlink(rover)= rover;
lo_mem_max= rover+1000;link(lo_mem_max)= null;info(lo_mem_max)= null;
for(k= hi_mem_stat_min;k<=mem_top;k++)
mem[k]= mem[lo_mem_max];
/*817:*/
#line 15626 "dummy.w"

info(omit_template)= end_template_token;

/*:817*//*824:*/
#line 15732 "dummy.w"

link(end_span)= max_quarterword+1;info(end_span)= null;

/*:824*//*848:*/
#line 16188 "dummy.w"

type(last_active)= hyphenated;line_number(last_active)= max_halfword;
subtype(last_active)= 0;

/*:848*//*1020:*/
#line 19275 "dummy.w"

subtype(page_ins_head)= qi(255);
type(page_ins_head)= split_up;link(page_ins_head)= page_ins_head;

/*:1020*//*1028:*/
#line 19422 "dummy.w"

type(page_head)= glue_node;subtype(page_head)= normal;

/*:1028*/
#line 3454 "dummy.w"
;
avail= null;
hi_mem_min= hi_mem_stat_min;
var_used= lo_mem_stat_max+1-mem_bot;dyn_used= hi_mem_stat_usage;


/*:178*/
#line 3434 "dummy.w"

}

/*:177*//*188:*/
#line 3625 "dummy.w"

int font_in_short_display;

/*:188*//*190:*/
#line 3631 "dummy.w"

void short_display(int p)
{int n;
while(p> mem_min)
{if(is_char_node(p))
{if(p<=mem_end)
{if(font(p)!=font_in_short_display)
{if((font(p)<font_base)||(font(p)> font_max))
print_char('*');

else/*288:*/
#line 5900 "dummy.w"

print_char('\\');
if(font_name[font(p)]!=NULL)print_str(font_name[font(p)]);else print_char('*');

/*:288*/
#line 3641 "dummy.w"
;
print_char(' ');font_in_short_display= font(p);
}
print_ASCII(qo(character(p)));
}
}
else/*191:*/
#line 3652 "dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case ins_node:case whatsit_node:case mark_node:case adjust_node:
case unset_node:print_str("[]");break;
case rule_node:print_char('|');break;
case glue_node:if(glue_ptr(p)!=zero_glue)print_char(' ');break;
case math_node:print_char('$');break;
case ligature_node:short_display(lig_ptr(p));break;
case disc_node:{short_display(pre_break(p));
short_display(post_break(p));
n= replace_count(p);
while(n> 0)
{if(link(p)!=null)p= link(p);
decr(n);
}
}break;
default:do_nothing;
}

/*:191*/
#line 3647 "dummy.w"
;
p= link(p);
}
}

/*:190*//*192:*/
#line 3675 "dummy.w"

void print_font_and_char(int p)
{if(p> mem_end)print_esc(/*1432:*/
#line 25519 "dummy.w"
261
/*:1432*/
#line 3677 "dummy.w"
);
else{/*288:*/
#line 5900 "dummy.w"

print_char('\\');
if(font_name[font(p)]!=NULL)print_str(font_name[font(p)]);else print_char('*');

/*:288*/
#line 3678 "dummy.w"
;
print_char(' ');print_ASCII(character(p));
}
}

void print_mark(int p)
{print_char('{');print_char('}');
}

void print_rule_dimen(scaled d)
{if(is_running(d))print_char('*');else print_scaled(d);

}

/*:192*//*194:*/
#line 3695 "dummy.w"

void print_glue(scaled d,int order,str_number s)

{print_scaled(d);
if((order<normal)||(order> filll))print_str("foul");
else if(order> normal)
{print_str("fil");
while(order> fil)
{print_char('l');decr(order);
}
}
else if(s!=0)print(s);
}

/*:194*//*196:*/
#line 3711 "dummy.w"

void print_spec(int p,str_number s)

{if((p<mem_min)||(p>=lo_mem_max))print_char('*');

else{print_scaled(width(p));
if(s!=0)print(s);
if(stretch(p)!=0)
{print_str(" plus ");print_glue(stretch(p),stretch_order(p),s);
}
if(shrink(p)!=0)
{print_str(" minus ");print_glue(shrink(p),shrink_order(p),s);
}
}
}

/*:196*//*198:*/
#line 3741 "dummy.w"


static int depth_level= 0;

#define node_list_display(X) {depth_level++;show_node_list(X);depth_level--;}

/*:198*//*201:*/
#line 3770 "dummy.w"

void show_node_list(int p)
{
int n;
double g;
if(cur_length> depth_threshold)
{if(p> null)print_str(" []");

return;
}
n= 0;
while(p> mem_min)
{{int i;print_ln();for(i= 0;i<depth_level;i++)print_char('.');}
if(p> mem_end)
{print_str("Bad link, display aborted.");return;

}
incr(n);if(n> breadth_max)
{print_str("etc.");return;

}
/*202:*/
#line 3797 "dummy.w"

if(is_char_node(p))print_font_and_char(p);
else switch(type(p)){
case hlist_node:case vlist_node:case unset_node:/*203:*/
#line 3814 "dummy.w"

{if(type(p)==hlist_node)print_esc('h');
else if(type(p)==vlist_node)print_esc('v');
else print_esc(/*1434:*/
#line 25525 "dummy.w"
263
/*:1434*/
#line 3817 "dummy.w"
);
print_str("box(");print_scaled(height(p));print_char('+');
print_scaled(depth(p));print_str(")x");print_scaled(width(p));
if(type(p)==unset_node)
/*204:*/
#line 3830 "dummy.w"

{if(span_count(p)!=min_quarterword)
{print_str(" (");print_int(qo(span_count(p))+1);
print_str(" columns)");
}
if(glue_stretch(p)!=0)
{print_str(", stretch ");print_glue(glue_stretch(p),glue_order(p),0);
}
if(glue_shrink(p)!=0)
{print_str(", shrink ");print_glue(glue_shrink(p),glue_sign(p),0);
}
}

/*:204*/
#line 3821 "dummy.w"

else{/*205:*/
#line 3853 "dummy.w"

g= float(glue_set(p));
if((g!=float_constant(0))&&(glue_sign(p)!=normal))
{print_str(", glue set ");
if(glue_sign(p)==shrinking)print_str("- ");
if(abs(mem[p+glue_offset].i)<04000000)print_str("?.?");
else if(abs(g)> float_constant(20000))
{if(g> float_constant(0))print_char('>');
else print_str("< -");
print_glue(20000*unity,glue_order(p),0);
}
else print_glue(round(unity*g),glue_order(p),0);

}

/*:205*/
#line 3822 "dummy.w"
;
if(shift_amount(p)!=0)
{print_str(", shifted ");print_scaled(shift_amount(p));
}
}
node_list_display(list_ptr(p));
}

/*:203*/
#line 3800 "dummy.w"
break;
case rule_node:/*206:*/
#line 3868 "dummy.w"

{print_esc(/*1435:*/
#line 25528 "dummy.w"
264
/*:1435*/
#line 3869 "dummy.w"
);print_rule_dimen(height(p));print_char('+');
print_rule_dimen(depth(p));print_str(")x");print_rule_dimen(width(p));
}

/*:206*/
#line 3801 "dummy.w"
break;
case ins_node:/*207:*/
#line 3873 "dummy.w"

{print_esc(/*1436:*/
#line 25531 "dummy.w"
265
/*:1436*/
#line 3874 "dummy.w"
);print_int(qo(subtype(p)));
print_str(", natural size ");print_scaled(height(p));
print_str("; split(");print_spec(split_top_ptr(p),0);
print_char(',');print_scaled(depth(p));
print_str("); float cost ");print_int(float_cost(p));
node_list_display(ins_ptr(p));
}

/*:207*/
#line 3802 "dummy.w"
break;
case whatsit_node:/*1401:*/
#line 24958 "dummy.w"

switch(subtype(p)){
case special_node:{print_esc(/*1831:*/
#line 26716 "dummy.w"
660
/*:1831*/
#line 24960 "dummy.w"
);
print_mark(write_tokens(p));
}break;
case language_node:{print_esc(/*1833:*/
#line 26722 "dummy.w"
662
/*:1833*/
#line 24963 "dummy.w"
);
print_int(what_lang(p));print_str(" (hyphenmin ");
print_int(what_lhm(p));print_char(',');
print_int(what_rhm(p));print_char(')');
}break;
case par_node:print_str("\\parameter ");
print_int(par_type(p));print_char(',');print_int(par_number(p));
print_char(':');print_int(par_value(p).i);
break;
case graf_node:print_str("\\paragraf(");
print_int(graf_penalty(p));
print_char(')');
node_list_display(graf_params(p));
node_list_display(graf_list(p));
print_xdimen(graf_extent(p));
break;
case disp_node:print_str("\\display ");
node_list_display(display_eqno(p));
if(display_left(p))print_str("left ");else print_str("right ");
node_list_display(display_formula(p));
node_list_display(display_params(p));
break;
case baseline_node:print_str("\\baselineskip ");
print_baseline_skip(baseline_node_no(p));
break;
case hset_node:case vset_node:
print_char('\\');
print_char(subtype(p)==hset_node?'h':'v');
print_str("set(");
print_scaled(height(p));print_char('+');
print_scaled(depth(p));print_str(")x");print_scaled(width(p));
if(shift_amount(p)!=0)
{print_str(", shifted ");print_scaled(shift_amount(p));
}
if(set_stretch(p)!=0)
{print_str(", stretch ");print_glue(set_stretch(p),set_stretch_order(p),/*1471:*/
#line 25636 "dummy.w"
300
/*:1471*/
#line 24998 "dummy.w"
);
}
if(set_shrink(p)!=0)
{print_str(", shrink ");print_glue(set_shrink(p),set_shrink_order(p),/*1471:*/
#line 25636 "dummy.w"
300
/*:1471*/
#line 25001 "dummy.w"
);
}
print_str(", extent ");print_xdimen(set_extent(p));
node_list_display(list_ptr(p));
break;
case hpack_node:case vpack_node:
print_char('\\');
print_char(subtype(p)==hpack_node?'h':'v');
print_str("pack(");
print_str(pack_m(p)==exactly?"exactly ":"additional ");
print_xdimen(pack_extent(p));
if(subtype(p)==vpack_node&&pack_limit(p)!=max_dimen){print_str(", limit ");print_scaled(pack_limit(p));}
print_char(')');
node_list_display(list_ptr(p));
break;
case image_node:
print_str("\\image(");
print_char('(');print_scaled(image_height(p));
print_char('+');print_scaled(image_depth(p));
print_str(")x");print_scaled(image_width(p));
if(image_stretch(p)!=0){print_str(" plus ");print_glue(image_stretch(p),image_stretch_order(p),/*1471:*/
#line 25636 "dummy.w"
300
/*:1471*/
#line 25021 "dummy.w"
);}
if(image_shrink(p)!=0){print_str(" minus ");print_glue(image_shrink(p),image_shrink_order(p),/*1471:*/
#line 25636 "dummy.w"
300
/*:1471*/
#line 25022 "dummy.w"
);}
print_str(", section ");print_int(image_no(p));
if(image_name(p)!=0){print_str(", ");print(image_name(p));}
break;
case align_node:
print_str("\\align(");
print_str(align_m(p)==exactly?"exactly ":"additional ");
print_xdimen(align_extent(p));print_char(')');
node_list_display(align_preamble(p));
print_char(':');
node_list_display(align_list(p));
break;
case setpage_node:
print_str("\\setpage");print_int(setpage_number(p));print_char(' ');print(setpage_name(p));
print_str(" priority ");print_int(setpage_priority(p));
print_str(" width ");print_xdimen(setpage_width(p));
print_str(" height ");print_xdimen(setpage_height(p));
print_ln();print_current_string();print_str(".\\topskip=");print_spec(setpage_topskip(p),0);
print_ln();print_current_string();print_str(".\\maxdepth=");print_scaled(setpage_depth(p));
node_list_display(setpage_list(p));
node_list_display(setpage_streams(p));
break;
case setstream_node:
print_str("\\setstream");print_int(setstream_insertion(p));
print_char('(');print_int(setstream_number(p));print_char(')');
if(setstream_prefered(p)!=255){print_str(" prefered ");print_int(setstream_prefered(p));}
if(setstream_ratio(p)> 0){print_str(" ratio ");print_int(setstream_ratio(p));}
if(setstream_next(p)!=255){print_str(" next ");print_int(setstream_next(p));}
append_char('.');
print_ln();print_current_string();print_str("\\count");print_int(setstream_insertion(p));print_char('=');
print_int(setstream_mag(p));
print_ln();print_current_string();print_str("\\dimen");print_int(setstream_insertion(p));print_char('=');
print_xdimen(setstream_max(p));
print_ln();print_current_string();print_str("\\skip");print_int(setstream_insertion(p));print_char('=');
print_spec(setstream_height(p),0);
print_ln();print_current_string();print_str("\\hsize=");print_xdimen(setstream_width(p));
print_ln();print_current_string();print_str("\\topskip=");print_spec(setstream_topskip(p),0);
if(setstream_before(p)!=null){print_ln();print_current_string();print_str("\\before");node_list_display(setstream_before(p));}
if(setstream_after(p)!=null){print_ln();print_current_string();print_str("\\after");node_list_display(setstream_after(p));}
flush_char;
break;
case stream_node:
print_str("\\stream");print_int(stream_insertion(p));
print_char('(');print_int(stream_number(p));print_char(')');
break;
case xdimen_node:
print_str("\\xdimen ");print_xdimen(p);
break;
default:print_str("whatsit?");
}

/*:1401*/
#line 3803 "dummy.w"
break;
case glue_node:/*208:*/
#line 3882 "dummy.w"

if(subtype(p)>=a_leaders)/*209:*/
#line 3886 "dummy.w"

{print_esc(empty_string);
if(subtype(p)==c_leaders)print_char('c');
else if(subtype(p)==x_leaders)print_char('x');
print_str("leaders ");print_spec(glue_ptr(p),0);
node_list_display(leader_ptr(p));
}

/*:209*/
#line 3883 "dummy.w"

else{print_str("\\glue ");print_spec(glue_ptr(p),0);}

/*:208*/
#line 3804 "dummy.w"
break;
case kern_node:/*210:*/
#line 3896 "dummy.w"

if(subtype(p)!=mu_glue)
{print_esc(/*1442:*/
#line 25549 "dummy.w"
271
/*:1442*/
#line 3898 "dummy.w"
);
print_char(' ');
print_scaled(width(p));
if(subtype(p)==acc_kern)print_str(" (for accent)");

}
else{print_esc(/*1443:*/
#line 25552 "dummy.w"
272
/*:1443*/
#line 3904 "dummy.w"
);print_scaled(width(p));print_str("mu");
}

/*:210*/
#line 3805 "dummy.w"
break;
case math_node:/*211:*/
#line 3907 "dummy.w"

{print_esc(/*1444:*/
#line 25555 "dummy.w"
273
/*:1444*/
#line 3908 "dummy.w"
);
if(subtype(p)==before)print_str("on");
else print_str("off");
if(width(p)!=0)
{print_str(", surrounded ");print_scaled(width(p));
}
}

/*:211*/
#line 3806 "dummy.w"
break;
case ligature_node:/*212:*/
#line 3916 "dummy.w"

{print_font_and_char(lig_char(p));print_str(" (ligature ");
if(subtype(p)> 1)print_char('|');
node_list_display(lig_ptr(p));
if(odd(subtype(p)))print_char('|');
print_char(')');
}

/*:212*/
#line 3807 "dummy.w"
break;
case penalty_node:/*213:*/
#line 3924 "dummy.w"

{print_esc(/*1445:*/
#line 25558 "dummy.w"
274
/*:1445*/
#line 3925 "dummy.w"
);print_int(penalty(p));
}

/*:213*/
#line 3808 "dummy.w"
break;
case disc_node:/*214:*/
#line 3931 "dummy.w"

{print_esc(/*1446:*/
#line 25561 "dummy.w"
275
/*:1446*/
#line 3932 "dummy.w"
);
if(replace_count(p)> 0)
{print_str(" replacing ");print_int(replace_count(p));
}
node_list_display(pre_break(p));
node_list_display(post_break(p));
}

/*:214*/
#line 3809 "dummy.w"
break;
case adjust_node:/*216:*/
#line 3944 "dummy.w"

{print_esc(/*1448:*/
#line 25567 "dummy.w"
277
/*:1448*/
#line 3945 "dummy.w"
);node_list_display(adjust_ptr(p));
}

/*:216*/
#line 3810 "dummy.w"
break;
default:print_str("Unknown node type!");
}

/*:202*/
#line 3791 "dummy.w"
;
p= link(p);
}

}

/*:201*//*218:*/
#line 3951 "dummy.w"

void show_box(pointer p)
{depth_threshold= 200;breadth_max= 200;
show_node_list(p);
print_ln();
}

/*:218*//*221:*/
#line 3986 "dummy.w"
void delete_glue_ref(pointer p)
fast_delete_glue_ref(p)
void delete_xdimen_ref(pointer p)
{if(xdimen_ref_count(p)==null)free_node(p,xdimen_node_size);
else decr(xdimen_ref_count(p));
}

/*:221*//*222:*/
#line 3998 "dummy.w"

void flush_node_list(pointer p)
{
pointer q;
while(p!=null)

{q= link(p);
if(is_char_node(p))free_avail(p)
else{switch(type(p)){
case hlist_node:case vlist_node:case unset_node:{flush_node_list(list_ptr(p));
free_node(p,box_node_size);goto done;
}
case rule_node:{free_node(p,rule_node_size);goto done;
}
case ins_node:{flush_node_list(ins_ptr(p));
delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);goto done;
}
case whatsit_node:goto done;
case glue_node:{fast_delete_glue_ref(glue_ptr(p));
if(leader_ptr(p)!=null)flush_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:do_nothing;break;
case ligature_node:flush_node_list(lig_ptr(p));break;
case disc_node:{flush_node_list(pre_break(p));
flush_node_list(post_break(p));
}break;
case adjust_node:flush_node_list(adjust_ptr(p));break;
default:QUIT("Confusion while flushing node list");

}
free_node(p,small_node_size);
done:;}
p= q;
}
}

/*:222*//*224:*/
#line 4060 "dummy.w"

pointer copy_node_list(pointer p)

{pointer h;
pointer q;
pointer r;
uint8_t words;
h= get_avail();q= h;
while(p!=null)
{/*225:*/
#line 4076 "dummy.w"

words= 1;
if(is_char_node(p))r= get_avail();
else/*226:*/
#line 4085 "dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case unset_node:{r= get_node(box_node_size);
mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case rule_node:{r= get_node(rule_node_size);words= rule_node_size;
}break;
case ins_node:{r= get_node(ins_node_size);mem[r+4]= mem[p+4];
add_glue_ref(split_top_ptr(p));
ins_ptr(r)= copy_node_list(ins_ptr(p));
words= ins_node_size-1;
}break;
case whatsit_node:/*1403:*/
#line 25085 "dummy.w"

switch(subtype(p)){
case open_node:{r= get_node(open_node_size);words= open_node_size;
}break;
case write_node:case special_node:{r= get_node(write_node_size);
add_token_ref(write_tokens(p));words= write_node_size;
}break;
case close_node:case language_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case par_node:
{r= get_node(par_node_size);
if(par_type(p)==glue_type)add_glue_ref(par_value(p).i);
words= par_node_size;
}break;
case graf_node:
{r= get_node(graf_node_size);
add_xdimen_ref(graf_extent(p));
graf_params(r)= copy_node_list(graf_params(p));
graf_list(r)= copy_node_list(graf_list(p));
words= graf_node_size-1;
}break;
case disp_node:
{r= get_node(disp_node_size);
display_left(r)= display_left(p);
display_eqno(r)= copy_node_list(display_eqno(p));
display_formula(r)= copy_node_list(display_formula(p));
display_params(r)= copy_node_list(display_params(p));
words= disp_node_size-2;
}break;
case baseline_node:
{r= get_node(baseline_node_size);
words= baseline_node_size;
}break;
case hpack_node:case vpack_node:
{r= get_node(pack_node_size);
pack_m(r)= pack_m(p);
list_ptr(r)= copy_node_list(list_ptr(p));
add_xdimen_ref(pack_extent(p));
pack_limit(r)= pack_limit(p);
words= pack_node_size-3;
}break;
case hset_node:case vset_node:
{r= get_node(set_node_size);
mem[r+8]= mem[p+8];mem[r+7]= mem[p+7];mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
add_xdimen_ref(set_extent(p));
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case image_node:
r= get_node(image_node_size);
words= image_node_size;
break;
case align_node:
{r= get_node(align_node_size);
align_preamble(r)= copy_node_list(align_preamble(p));
align_list(r)= copy_node_list(align_list(p));
add_xdimen_ref(align_extent(p));
words= align_node_size-1;
}break;
case setpage_node:
{r= get_node(setpage_node_size);
add_glue_ref(setpage_topskip(p));
add_xdimen_ref(setpage_height(p));
add_xdimen_ref(setpage_width(p));
setpage_list(r)= copy_node_list(setpage_list(p));
setpage_streams(r)= copy_node_list(setpage_streams(p));
words= setpage_node_size-1;
}break;
case setstream_node:
{r= get_node(setstream_node_size);
add_xdimen_ref(setstream_max(p));
add_xdimen_ref(setstream_width(p));
add_glue_ref(setstream_topskip(p));
add_glue_ref(setstream_height(p));
setstream_before(r)= copy_node_list(setstream_before(p));
setstream_after(r)= copy_node_list(setstream_after(p));
words= setstream_node_size-1;
}break;
case stream_node:
r= get_node(stream_node_size);
words= stream_node_size;
break;
case xdimen_node:
r= get_node(xdimen_node_size);
words= xdimen_node_size;
break;
default:confusion(/*1835:*/
#line 26728 "dummy.w"
664
/*:1835*/
#line 25172 "dummy.w"
);

}

/*:1403*/
#line 4100 "dummy.w"
break;
case glue_node:{r= get_node(small_node_size);add_glue_ref(glue_ptr(p));
glue_ptr(r)= glue_ptr(p);leader_ptr(r)= copy_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case ligature_node:{r= get_node(small_node_size);
mem[lig_char(r)]= mem[lig_char(p)];
lig_ptr(r)= copy_node_list(lig_ptr(p));
}break;
case disc_node:{r= get_node(small_node_size);
pre_break(r)= copy_node_list(pre_break(p));
post_break(r)= copy_node_list(post_break(p));
}break;
case mark_node:{r= get_node(small_node_size);add_token_ref(mark_ptr(p));
words= small_node_size;
}break;
case adjust_node:{r= get_node(small_node_size);
adjust_ptr(r)= copy_node_list(adjust_ptr(p));
}break;
default:confusion(/*1450:*/
#line 25573 "dummy.w"
279
/*:1450*/
#line 4121 "dummy.w"
);

}

/*:226*/
#line 4080 "dummy.w"
;
while(words> 0)
{decr(words);mem[r+words]= mem[p+words];
}

/*:225*/
#line 4069 "dummy.w"
;
link(q)= r;q= r;p= link(p);
}
link(q)= null;q= link(h);free_avail(h);
return q;
}

/*:224*//*235:*/
#line 4451 "dummy.w"


/*233:*/
#line 4431 "dummy.w"

list_state_record nest[nest_size+1];
uint16_t nest_ptr;
uint16_t max_nest_stack;
list_state_record cur_list;
int16_t shown_mode;

/*:233*/
#line 4453 "dummy.w"


void list_init(void)
{
nest_ptr= 0;max_nest_stack= 0;
memset(&cur_list,0,sizeof(cur_list));
mode= vmode;head= contrib_head;tail= contrib_head;
prev_height= prev_depth= ignore_depth;
}
/*:235*//*237:*/
#line 4471 "dummy.w"

void push_nest(void)
{if(nest_ptr> max_nest_stack)
{max_nest_stack= nest_ptr;
if(nest_ptr==nest_size)overflow("semantic nest size",nest_size);

}
nest[nest_ptr]= cur_list;
incr(nest_ptr);head= get_avail();tail= head;prev_graf= 0;
cur_list.bs_pos= NULL;cur_bs= baseline_skip;cur_ls= line_skip;cur_lsl= line_skip_limit;
}

/*:237*//*238:*/
#line 4488 "dummy.w"

void pop_nest(void)
{free_avail(head);decr(nest_ptr);cur_list= nest[nest_ptr];
}

/*:238*//*571:*/
#line 10802 "dummy.w"

memory_word font_info[font_mem_size+1];

static font_index fmem_ptr= 0;

void hclear_fonts(void)
{fmem_ptr= 0;
}
internal_font_number font_ptr;
four_quarters font_check0[font_max-font_base+1],*const font_check= font_check0-font_base;
scaled font_size0[font_max-font_base+1],*const font_size= font_size0-font_base;
scaled font_dsize0[font_max-font_base+1],*const font_dsize= font_dsize0-font_base;
font_index font_params0[font_max-font_base+1],*const font_params= font_params0-font_base;

char*font_name0[font_max-font_base+1],**const font_name= font_name0-font_base;
eight_bits font_bc0[font_max-font_base+1],*const font_bc= font_bc0-font_base;

eight_bits font_ec0[font_max-font_base+1],*const font_ec= font_ec0-font_base;

pointer font_glue0[font_max-font_base+1],*const font_glue= font_glue0-font_base;

bool font_used0[font_max-font_base+1],*const font_used= font_used0-font_base;

int hyphen_char0[font_max-font_base+1],*const hyphen_char= hyphen_char0-font_base;

int skew_char0[font_max-font_base+1],*const skew_char= skew_char0-font_base;

font_index bchar_label0[font_max-font_base+1],*const bchar_label= bchar_label0-font_base;


uint16_t font_bchar0[font_max-font_base+1],*const font_bchar= font_bchar0-font_base;

uint16_t font_false_bchar0[font_max-font_base+1],*const font_false_bchar= font_false_bchar0-font_base;


/*:571*//*572:*/
#line 10846 "dummy.w"

int char_base0[font_max-font_base+1],*const char_base= char_base0-font_base;

int width_base0[font_max-font_base+1],*const width_base= width_base0-font_base;

int height_base0[font_max-font_base+1],*const height_base= height_base0-font_base;

int depth_base0[font_max-font_base+1],*const depth_base= depth_base0-font_base;

int italic_base0[font_max-font_base+1],*const italic_base= italic_base0-font_base;

int lig_kern_base0[font_max-font_base+1],*const lig_kern_base= lig_kern_base0-font_base;

int kern_base0[font_max-font_base+1],*const kern_base= kern_base0-font_base;

int exten_base0[font_max-font_base+1],*const exten_base= exten_base0-font_base;

int param_base0[font_max-font_base+1],*const param_base= param_base0-font_base;


/*:572*//*582:*/
#line 10999 "dummy.w"

void read_font_info(int f,char*nom,scaled s)
{
font_index k;
bool file_opened;
halfword lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np;

eight_bits a,b,c,d;
four_quarters qw;scaled sw;
int bch_label;
uint16_t bchar;
scaled z;
int alpha;uint8_t beta;

/*584:*/
#line 11048 "dummy.w"

/*585:*/
#line 11060 "dummy.w"

file_opened= true

/*:585*/
#line 11049 "dummy.w"
;
/*587:*/
#line 11084 "dummy.w"

{read_sixteen(lf);
fget;read_sixteen(lh);
fget;read_sixteen(bc);
fget;read_sixteen(ec);
if((bc> ec+1)||(ec> 255))abort;
if(bc> 255)
{bc= 1;ec= 0;
}
fget;read_sixteen(nw);
fget;read_sixteen(nh);
fget;read_sixteen(nd);
fget;read_sixteen(ni);
fget;read_sixteen(nl);
fget;read_sixteen(nk);
fget;read_sixteen(ne);
fget;read_sixteen(np);
if(lf!=6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np)abort;
if((nw==0)||(nh==0)||(nd==0)||(ni==0))abort;
}

/*:587*/
#line 11050 "dummy.w"
;
/*588:*/
#line 11111 "dummy.w"

lf= lf-6-lh;
if(np<7)lf= lf+7-np;
if((font_ptr==font_max)||(fmem_ptr+lf> font_mem_size))
QUIT("Not enough room left for font %s\n",nom);
char_base[f]= fmem_ptr-bc;
width_base[f]= char_base[f]+ec+1;
height_base[f]= width_base[f]+nw;
depth_base[f]= height_base[f]+nh;
italic_base[f]= depth_base[f]+nd;
lig_kern_base[f]= italic_base[f]+ni;
kern_base[f]= lig_kern_base[f]+nl-kern_base_offset;
exten_base[f]= kern_base[f]+kern_base_offset+nk;
param_base[f]= exten_base[f]+ne

/*:588*/
#line 11051 "dummy.w"
;
/*590:*/
#line 11139 "dummy.w"

{if(lh<2)abort;
store_four_quarters(font_check[f]);
fget;read_sixteen(z);
fget;z= z*0400+fbyte;fget;z= (z*020)+(fbyte/020);
if(z<unity)abort;
while(lh> 2)
{fget;fget;fget;fget;decr(lh);
}
font_dsize[f]= z;
if(s!=-1000)
if(s>=0)z= s;
else z= xn_over_d(z,-s,1000);
font_size[f]= z;
}

/*:590*/
#line 11052 "dummy.w"
;
/*591:*/
#line 11155 "dummy.w"

for(k= fmem_ptr;k<=width_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if((a>=nw)||(b/020>=nh)||(b%020>=nd)||
(c/4>=ni))abort;
switch(c%4){
case lig_tag:if(d>=nl)abort;break;
case ext_tag:if(d>=ne)abort;break;
case list_tag:/*592:*/
#line 11176 "dummy.w"

{check_byte_range(d);
while(d<current_character_being_worked_on)
{qw= char_info(f)(d);

if(char_tag(qw)!=list_tag)goto not_found;
d= qo(rem_byte(qw));
}
if(d==current_character_being_worked_on)abort;
not_found:;}

/*:592*/
#line 11163 "dummy.w"
break;
default:do_nothing;
}
}

/*:591*/
#line 11053 "dummy.w"
;
/*593:*/
#line 11211 "dummy.w"

{/*594:*/
#line 11221 "dummy.w"

{alpha= 16;
while(z>=040000000)
{z= z/2;alpha= alpha+alpha;
}
beta= 256/alpha;alpha= alpha*z;
}

/*:594*/
#line 11212 "dummy.w"
;
for(k= width_base[f];k<=lig_kern_base[f]-1;k++)
store_scaled(font_info[k].sc);
if(font_info[width_base[f]].sc!=0)abort;
if(font_info[height_base[f]].sc!=0)abort;
if(font_info[depth_base[f]].sc!=0)abort;
if(font_info[italic_base[f]].sc!=0)abort;
}

/*:593*/
#line 11054 "dummy.w"
;
/*595:*/
#line 11235 "dummy.w"

bch_label= 077777;bchar= 256;
if(nl> 0)
{for(k= lig_kern_base[f];k<=kern_base[f]+kern_base_offset-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a> 128)
{if(256*c+d>=nl)abort;
if(a==255)if(k==lig_kern_base[f])bchar= b;
}
else{if(b!=bchar)check_existence(b);
if(c<128)check_existence(d)
else if(256*(c-128)+d>=nk)abort;
if(a<128)if(k-lig_kern_base[f]+a+1>=nl)abort;
}
}
if(a==255)bch_label= 256*c+d;
}
for(k= kern_base[f]+kern_base_offset;k<=exten_base[f]-1;k++)
store_scaled(font_info[k].sc);

/*:595*/
#line 11055 "dummy.w"
;
/*596:*/
#line 11255 "dummy.w"

for(k= exten_base[f];k<=param_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a!=0)check_existence(a);
if(b!=0)check_existence(b);
if(c!=0)check_existence(c);
check_existence(d);
}

/*:596*/
#line 11056 "dummy.w"
;
/*597:*/
#line 11267 "dummy.w"

{for(k= 1;k<=np;k++)
if(k==1)
{fget;sw= fbyte;if(sw> 127)sw= sw-256;
fget;sw= sw*0400+fbyte;fget;sw= sw*0400+fbyte;
fget;font_info[param_base[f]].sc= 
(sw*020)+(fbyte/020);
}
else store_scaled(font_info[param_base[f]+k-1].sc);
if(hpos>=hend)abort;
for(k= np+1;k<=7;k++)font_info[param_base[f]+k-1].sc= 0;
}

/*:597*/
#line 11057 "dummy.w"
;
/*598:*/
#line 11287 "dummy.w"

if(np>=7)font_params[f]= np;else font_params[f]= 7;
hyphen_char[f]= skew_char[f]= -1;
if(bch_label<nl)bchar_label[f]= bch_label+lig_kern_base[f];
else bchar_label[f]= non_address;
font_bchar[f]= qi(bchar);
font_false_bchar[f]= qi(bchar);
if(bchar<=ec)if(bchar>=bc)
{qw= char_info(f)(bchar);
if(char_exists(qw))font_false_bchar[f]= non_char;
}
font_name[f]= nom;
font_bc[f]= bc;font_ec[f]= ec;font_glue[f]= null;
adjust(char_base);adjust(width_base);adjust(lig_kern_base);
adjust(kern_base);adjust(exten_base);
decr(param_base[f]);
fmem_ptr= fmem_ptr+lf;goto done

/*:598*/
#line 11058 "dummy.w"


/*:584*/
#line 11015 "dummy.w"
;
bad_tfm:QUIT("Bad tfm file: %s\n",nom);
done:;
}

/*:582*//*604:*/
#line 11390 "dummy.w"

pointer new_character(internal_font_number f,eight_bits c)
{pointer p;
#ifdef DEBUG
if(font_bc[f]> c||font_ec[f]<c||!char_exists(char_info(f)(c)))
DBG(DBGFONT,"Warning: Character 0x%0X in font %d does not exist\n",c,f);
#endif
p= get_avail();font(p)= f;character(p)= c;
return p;
}

/*:604*//*674:*/
#line 12983 "dummy.w"

/*669:*/
#line 12964 "dummy.w"

scaled total_stretch0[filll-normal+1],*const total_stretch= total_stretch0-normal,total_shrink0[filll-normal+1],*const total_shrink= total_shrink0-normal;

int last_badness;

/*:669*//*672:*/
#line 12976 "dummy.w"

pointer adjust_tail;

/*:672*/
#line 12984 "dummy.w"


pointer hpack(pointer p,scaled w,small_number m)
{
pointer r;
pointer q;
scaled h,d,x;
scaled s;
pointer g;
glue_ord o;
internal_font_number f;
four_quarters i;
eight_bits hd;
r= get_node(box_node_size);type(r)= hlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
q= r+list_offset;link(q)= p;
h= 0;/*675:*/
#line 13011 "dummy.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:675*/
#line 13000 "dummy.w"
;
while(p!=null)/*676:*/
#line 13018 "dummy.w"


{reswitch:while(is_char_node(p))
/*679:*/
#line 13061 "dummy.w"

{f= font(p);i= char_info(f)(character(p));hd= height_depth(i);
x= x+char_width(f)(i);
s= char_height(f)(hd);if(s> h)h= s;
s= char_depth(f)(hd);if(s> d)d= s;
p= link(p);
}

/*:679*/
#line 13022 "dummy.w"
;
if(p!=null)
{switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*678:*/
#line 13049 "dummy.w"

{x= x+width(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(height(p)-s> h)h= height(p)-s;
if(depth(p)+s> d)d= depth(p)+s;
}

/*:678*/
#line 13026 "dummy.w"
break;
case ins_node:case mark_node:case adjust_node:if(adjust_tail!=null)
/*680:*/
#line 13076 "dummy.w"

{while(link(q)!=p)q= link(q);
if(type(p)==adjust_node)
{link(adjust_tail)= adjust_ptr(p);
while(link(adjust_tail)!=null)adjust_tail= link(adjust_tail);
p= link(p);free_node(link(q),small_node_size);
}
else{link(adjust_tail)= p;adjust_tail= p;p= link(p);
}
link(q)= p;p= q;
}

/*:680*/
#line 13028 "dummy.w"
break;
case whatsit_node:/*1406:*/
#line 25246 "dummy.w"

{glue_ord o;
if(image_height(p)> h)h= image_height(p);
x= x+image_width(p);
o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}

/*:1406*/
#line 13029 "dummy.w"
;break;
case glue_node:/*681:*/
#line 13088 "dummy.w"

{g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(height(g)> h)h= height(g);
if(depth(g)> d)d= depth(g);
}
}

/*:681*/
#line 13030 "dummy.w"
break;
case kern_node:case math_node:x= x+width(p);break;
case ligature_node:/*677:*/
#line 13040 "dummy.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:677*/
#line 13032 "dummy.w"

default:do_nothing;
}
p= link(p);
}
}


/*:676*/
#line 13003 "dummy.w"
;
if(adjust_tail!=null)link(adjust_tail)= null;
height(r)= h;depth(r)= d;
/*682:*/
#line 13102 "dummy.w"

if(m==additional)w= x+w;
width(r)= w;x= w-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*683:*/
#line 13114 "dummy.w"

{/*684:*/
#line 13125 "dummy.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:684*/
#line 13115 "dummy.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}

/*:683*/
#line 13111 "dummy.w"

else/*689:*/
#line 13170 "dummy.w"

{/*690:*/
#line 13183 "dummy.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:690*/
#line 13171 "dummy.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}

/*:689*/
#line 13112 "dummy.w"


/*:682*/
#line 13007 "dummy.w"
;
end:return r;
}

/*:674*//*695:*/
#line 13223 "dummy.w"

pointer vpackage(pointer p,scaled h,small_number m,scaled l)
{
pointer r;
scaled w,d,x;
scaled s;
pointer g;
glue_ord o;
r= get_node(box_node_size);type(r)= vlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
list_ptr(r)= p;
w= 0;/*675:*/
#line 13011 "dummy.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:675*/
#line 13234 "dummy.w"
;
while(p!=null)/*696:*/
#line 13247 "dummy.w"

{if(is_char_node(p))confusion(/*1690:*/
#line 26293 "dummy.w"
519
/*:1690*/
#line 13248 "dummy.w"
);

else switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*697:*/
#line 13262 "dummy.w"

{x= x+d+height(p);d= depth(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(width(p)+s> w)w= width(p)+s;
}

/*:697*/
#line 13252 "dummy.w"
break;
case whatsit_node:/*1405:*/
#line 25238 "dummy.w"

{glue_ord o;
if(image_width(p)> w)w= image_width(p);
x= x+d+image_height(p);d= 0;
o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}

/*:1405*/
#line 13253 "dummy.w"
;break;
case glue_node:/*698:*/
#line 13268 "dummy.w"

{x= x+d;d= 0;
g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(width(g)> w)w= width(g);
}
}

/*:698*/
#line 13254 "dummy.w"
break;
case kern_node:{x= x+d+width(p);d= 0;
}break;
default:do_nothing;
}
p= link(p);
}

/*:696*/
#line 13236 "dummy.w"
;
width(r)= w;
if(d> l)
{x= x+d-l;depth(r)= l;
}
else depth(r)= d;
/*699:*/
#line 13282 "dummy.w"

if(m==additional)h= x+h;
height(r)= h;x= h-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*700:*/
#line 13294 "dummy.w"

{/*684:*/
#line 13125 "dummy.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:684*/
#line 13295 "dummy.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}

/*:700*/
#line 13291 "dummy.w"

else/*703:*/
#line 13330 "dummy.w"

{/*690:*/
#line 13183 "dummy.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:690*/
#line 13331 "dummy.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}

/*:703*/
#line 13292 "dummy.w"


/*:699*/
#line 13243 "dummy.w"
;
end:return r;
}

/*:695*//*843:*/
#line 16089 "dummy.w"

/*671:*/
#line 12975 "dummy.w"

/*:671*//*842:*/
#line 16081 "dummy.w"

pointer just_box;

/*:842*//*850:*/
#line 16219 "dummy.w"

pointer passive;
pointer printed_node;
halfword pass_number;

/*:850*//*853:*/
#line 16259 "dummy.w"

scaled active_width0[6],*const active_width= active_width0-1;

scaled cur_active_width0[6],*const cur_active_width= cur_active_width0-1;
scaled background0[6],*const background= background0-1;
scaled break_width0[6],*const break_width= break_width0-1;

/*:853*//*856:*/
#line 16317 "dummy.w"

bool no_shrink_error_yet;

/*:856*//*860:*/
#line 16360 "dummy.w"

static pointer cur_p;
bool second_pass;
bool final_pass;
int threshold;

/*:860*//*866:*/
#line 16462 "dummy.w"

int minimal_demerits0[tight_fit-very_loose_fit+1],*const minimal_demerits= minimal_demerits0-very_loose_fit;

int minimum_demerits;

pointer best_place0[tight_fit-very_loose_fit+1],*const best_place= best_place0-very_loose_fit;

halfword best_pl_line0[tight_fit-very_loose_fit+1],*const best_pl_line= best_pl_line0-very_loose_fit;


/*:866*//*873:*/
#line 16581 "dummy.w"

scaled disc_width;

/*:873*//*882:*/
#line 16722 "dummy.w"

halfword easy_line;
halfword last_special_line;

scaled first_width;

scaled second_width;
scaled first_indent;
scaled second_indent;

/*:882*//*908:*/
#line 17226 "dummy.w"

pointer best_bet;
int fewest_demerits;
halfword best_line;
int actual_looseness;

int line_diff;


/*:908*/
#line 16090 "dummy.w"


/*706:*/
#line 13363 "dummy.w"

void append_to_vlist(pointer b,uint32_t offset)
{scaled d;
pointer p;
if(prev_depth> ignore_depth)
{d= width(baseline_skip)-prev_depth-height(b);
if(d<line_skip_limit)p= new_glue(line_skip);
else{temp_ptr= new_spec(baseline_skip);
p= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
width(temp_ptr)= d;
}
store_map(p,node_pos,offset);
link(tail)= p;tail= p;
}
link(tail)= b;tail= b;prev_depth= depth(b);
}

/*:706*//*857:*/
#line 16320 "dummy.w"

pointer finite_shrink(pointer p)
{pointer q;
QUIT("Infinite glue shrinkage found in a paragraph");
q= new_spec(p);shrink_order(q)= normal;
delete_glue_ref(p);return q;
}

/*:857*//*861:*/
#line 16383 "dummy.w"

void try_break(int pi,small_number break_type)
{
pointer r;
pointer prev_r;
halfword old_l;
bool no_break_yet;
/*862:*/
#line 16411 "dummy.w"

pointer prev_prev_r;
pointer s;
pointer q;
pointer v;
int t;
internal_font_number f;
halfword l;
bool node_r_stays_active;
scaled line_width;
uint8_t fit_class;
halfword b;
int d;
bool artificial_demerits;
#ifdef STAT
pointer save_link;
#endif
scaled shortfall;

/*:862*/
#line 16390 "dummy.w"

/*863:*/
#line 16430 "dummy.w"

if(abs(pi)>=inf_penalty)
if(pi> 0)goto end;
else pi= eject_penalty

/*:863*/
#line 16391 "dummy.w"
;
no_break_yet= true;prev_r= active;old_l= 0;
do_all_six(copy_to_cur_active);
loop{resume:r= link(prev_r);
/*864:*/
#line 16440 "dummy.w"


if(type(r)==delta_node)
{do_all_six(update_width);
prev_prev_r= prev_r;prev_r= r;goto resume;
}

/*:864*/
#line 16396 "dummy.w"
;
/*868:*/
#line 16486 "dummy.w"

{l= line_number(r);
if(l> old_l)
{
if((minimum_demerits<awful_bad)&&
((old_l!=easy_line)||(r==last_active)))
/*869:*/
#line 16504 "dummy.w"

{if(no_break_yet)/*870:*/
#line 16540 "dummy.w"

{no_break_yet= false;do_all_six(set_break_width_to_background);
s= cur_p;
if(break_type> unhyphenated)if(cur_p!=null)
/*874:*/
#line 16584 "dummy.w"

{t= replace_count(cur_p);v= cur_p;s= post_break(cur_p);
while(t> 0)
{decr(t);v= link(v);
/*875:*/
#line 16602 "dummy.w"

if(is_char_node(v))
{f= font(v);
break_width[1]= break_width[1]-char_width(f)(char_info(f)(character(v)));
}
else switch(type(v)){
case ligature_node:{f= font(lig_char(v));
break_width[1]= break_width[1]-
char_width(f)(char_info(f)(character(lig_char(v))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]-width(v);break;
default:confusion(/*1723:*/
#line 26392 "dummy.w"
552
/*:1723*/
#line 16614 "dummy.w"
);

}

/*:875*/
#line 16588 "dummy.w"
;
}
while(s!=null)
{/*876:*/
#line 16618 "dummy.w"

if(is_char_node(s))
{f= font(s);
break_width[1]= break_width[1]+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
break_width[1]= break_width[1]+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]+width(s);break;
default:confusion(/*1724:*/
#line 26395 "dummy.w"
553
/*:1724*/
#line 16630 "dummy.w"
);

}

/*:876*/
#line 16591 "dummy.w"
;
s= link(s);
}
break_width[1]= break_width[1]+disc_width;
if(post_break(cur_p)==null)s= link(v);

}

/*:874*/
#line 16544 "dummy.w"
;
while(s!=null)
{if(is_char_node(s))goto done;
switch(type(s)){
case glue_node:/*871:*/
#line 16559 "dummy.w"

{v= glue_ptr(s);break_width[1]= break_width[1]-width(v);
break_width[2+stretch_order(v)]= break_width[2+stretch_order(v)]-stretch(v);
break_width[6]= break_width[6]-shrink(v);
}

/*:871*/
#line 16548 "dummy.w"
break;
case penalty_node:do_nothing;break;
case math_node:break_width[1]= break_width[1]-width(s);break;
case kern_node:if(subtype(s)!=explicit)goto done;
else break_width[1]= break_width[1]-width(s);break;
default:goto done;
}
s= link(s);
}
done:;}

/*:870*/
#line 16505 "dummy.w"
;
/*877:*/
#line 16643 "dummy.w"

if(type(prev_r)==delta_node)
{do_all_six(convert_to_break_width);
}
else if(prev_r==active)
{do_all_six(store_break_width);
}
else{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_to_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:877*/
#line 16506 "dummy.w"
;
if(abs(adj_demerits)>=awful_bad-minimum_demerits)
minimum_demerits= awful_bad-1;
else minimum_demerits= minimum_demerits+abs(adj_demerits);
for(fit_class= very_loose_fit;fit_class<=tight_fit;fit_class++)
{if(minimal_demerits[fit_class]<=minimum_demerits)
/*879:*/
#line 16673 "dummy.w"

{q= get_node(passive_node_size);
link(q)= passive;passive= q;cur_break(q)= cur_p;
#ifdef STAT
incr(pass_number);serial(q)= pass_number;
#endif

prev_break(q)= best_place[fit_class];
q= get_node(active_node_size);break_node(q)= passive;
line_number(q)= best_pl_line[fit_class]+1;
fitness(q)= fit_class;type(q)= break_type;
total_demerits(q)= minimal_demerits[fit_class];
link(q)= r;link(prev_r)= q;prev_r= q;
#ifdef STAT
if(tracing_paragraphs> 0)
/*880:*/
#line 16693 "dummy.w"

{print_nl("@@");print_int(serial(passive));

print_str(": line ");print_int(line_number(q)-1);
print_char('.');print_int(fit_class);
if(break_type==hyphenated)print_char('-');
print_str(" t=");print_int(total_demerits(q));
print_str(" -> @@");
if(prev_break(passive)==null)print_char('0');
else print_int(serial(prev_break(passive)));
}

/*:880*/
#line 16688 "dummy.w"
;
#endif

}

/*:879*/
#line 16512 "dummy.w"
;
minimal_demerits[fit_class]= awful_bad;
}
minimum_demerits= awful_bad;
/*878:*/
#line 16662 "dummy.w"

if(r!=last_active)
{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_from_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:878*/
#line 16516 "dummy.w"
;
}

/*:869*/
#line 16492 "dummy.w"
;
if(r==last_active)goto end;
/*885:*/
#line 16767 "dummy.w"

if(l> easy_line)
{line_width= second_width;old_l= max_halfword-1;
}
else{old_l= l;
if(l> last_special_line)line_width= second_width;
else if(par_shape_ptr==null)line_width= first_width;
else line_width= mem[par_shape_ptr+2*l].sc;
}

/*:885*/
#line 16494 "dummy.w"
;
}
}

/*:868*/
#line 16399 "dummy.w"
;
/*886:*/
#line 16787 "dummy.w"

{artificial_demerits= false;

shortfall= line_width-cur_active_width[1];
if(shortfall> 0)
/*887:*/
#line 16817 "dummy.w"

if((cur_active_width[3]!=0)||(cur_active_width[4]!=0)||
(cur_active_width[5]!=0))
{b= 0;fit_class= decent_fit;
}
else{if(shortfall> 7230584)if(cur_active_width[2]<1663497)
{b= inf_bad;fit_class= very_loose_fit;goto done1;
}
b= badness(shortfall,cur_active_width[2]);
if(b> 12)
if(b> 99)fit_class= very_loose_fit;
else fit_class= loose_fit;
else fit_class= decent_fit;
done1:;
}

/*:887*/
#line 16793 "dummy.w"

else/*888:*/
#line 16836 "dummy.w"

{if(-shortfall> cur_active_width[6])b= inf_bad+1;
else b= badness(-shortfall,cur_active_width[6]);
if(b> 12)fit_class= tight_fit;else fit_class= decent_fit;
}

/*:888*/
#line 16795 "dummy.w"
;
if((b> inf_bad)||(pi==eject_penalty))
/*889:*/
#line 16851 "dummy.w"

{if(final_pass&&(minimum_demerits==awful_bad)&&
(link(r)==last_active)&&
(prev_r==active))
artificial_demerits= true;
else if(b> threshold)goto deactivate;
node_r_stays_active= false;
}

/*:889*/
#line 16798 "dummy.w"

else{prev_r= r;
if(b> threshold)goto resume;
node_r_stays_active= true;
}
/*890:*/
#line 16867 "dummy.w"

if(artificial_demerits)d= 0;
else/*894:*/
#line 16928 "dummy.w"

{d= line_penalty+b;
if(abs(d)>=10000)d= 100000000;else d= d*d;
if(pi!=0)
if(pi> 0)d= d+pi*pi;
else if(pi> eject_penalty)d= d-pi*pi;
if((break_type==hyphenated)&&(type(r)==hyphenated))
if(cur_p!=null)d= d+double_hyphen_demerits;
else d= d+final_hyphen_demerits;
if(abs(fit_class-fitness(r))> 1)d= d+adj_demerits;
}

/*:894*/
#line 16869 "dummy.w"
;
#ifdef STAT
if(tracing_paragraphs> 0)
/*891:*/
#line 16883 "dummy.w"

{if(printed_node!=cur_p)
/*892:*/
#line 16905 "dummy.w"

{print_nl("");
if(cur_p==null)short_display(link(printed_node));
else{save_link= link(cur_p);
link(cur_p)= null;print_nl("");short_display(link(printed_node));
link(cur_p)= save_link;
}
printed_node= cur_p;
}

/*:892*/
#line 16885 "dummy.w"
;
print_nl("@");

if(cur_p==null)print_esc(/*1615:*/
#line 26068 "dummy.w"
444
/*:1615*/
#line 16888 "dummy.w"
);
else if(type(cur_p)!=glue_node)
{if(type(cur_p)==penalty_node)print_esc(/*1599:*/
#line 26020 "dummy.w"
428
/*:1599*/
#line 16890 "dummy.w"
);
else if(type(cur_p)==disc_node)print_esc(/*1446:*/
#line 25561 "dummy.w"
275
/*:1446*/
#line 16891 "dummy.w"
);
else if(type(cur_p)==kern_node)print_esc(/*1442:*/
#line 25549 "dummy.w"
271
/*:1442*/
#line 16892 "dummy.w"
);
else print_esc(/*1444:*/
#line 25555 "dummy.w"
273
/*:1444*/
#line 16893 "dummy.w"
);
}
print_str(" via @@");
if(break_node(r)==null)print_char('0');
else print_int(serial(break_node(r)));
print_str(" b=");
if(b> inf_bad)print_char('*');else print_int(b);

print_str(" p=");print_int(pi);print_str(" d=");
if(artificial_demerits)print_char('*');else print_int(d);
}

/*:891*/
#line 16872 "dummy.w"
;
#endif

d= d+total_demerits(r);

if(d<=minimal_demerits[fit_class])
{minimal_demerits[fit_class]= d;
best_place[fit_class]= break_node(r);best_pl_line[fit_class]= l;
if(d<minimum_demerits)minimum_demerits= d;
}

/*:890*/
#line 16803 "dummy.w"
;
if(node_r_stays_active)goto resume;
deactivate:/*895:*/
#line 16950 "dummy.w"

link(prev_r)= link(r);free_node(r,active_node_size);
if(prev_r==active)/*896:*/
#line 16975 "dummy.w"

{r= link(active);
if(type(r)==delta_node)
{do_all_six(update_active);
do_all_six(copy_to_cur_active);
link(active)= link(r);free_node(r,delta_node_size);
}
}

/*:896*/
#line 16953 "dummy.w"

else if(type(prev_r)==delta_node)
{r= link(prev_r);
if(r==last_active)
{do_all_six(downdate_width);
link(prev_prev_r)= last_active;
free_node(prev_r,delta_node_size);prev_r= prev_prev_r;
}
else if(type(r)==delta_node)
{do_all_six(update_width);
do_all_six(combine_two_deltas);
link(prev_r)= link(r);free_node(r,delta_node_size);
}
}

/*:895*/
#line 16805 "dummy.w"
;
}

/*:886*/
#line 16402 "dummy.w"
;
}
end:;
#ifdef STAT
/*893:*/
#line 16920 "dummy.w"

if(cur_p==printed_node)if(cur_p!=null)if(type(cur_p)==disc_node)
{t= replace_count(cur_p);
while(t> 0)
{decr(t);printed_node= link(printed_node);
}
}

/*:893*/
#line 16406 "dummy.w"
;
#endif

}

/*:861*//*913:*/
#line 17297 "dummy.w"

void post_line_break(int final_widow_penalty)
{
pointer q,r,s;
bool disc_break;
bool post_disc_break;
bool first_line= true;
uint32_t line_offset,next_offset;
scaled cur_width;
scaled cur_indent;
quarterword t;
int pen;
halfword cur_line;
/*914:*/
#line 17347 "dummy.w"

q= break_node(best_bet);cur_p= null;
do{r= q;q= prev_break(q);next_break(r)= cur_p;cur_p= r;
}while(!(q==null))

/*:914*/
#line 17310 "dummy.w"
;
cur_line= prev_graf+1;
next_offset= hposition(link(temp_head));
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
do{
line_offset= next_offset;
{pointer q= cur_break(cur_p);
if(q==null)
next_offset= (hstart-hpos);
else
next_offset= hposition(q);
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
}
/*916:*/
#line 17384 "dummy.w"

/*917:*/
#line 17396 "dummy.w"

q= cur_break(cur_p);disc_break= false;post_disc_break= false;
if(q!=null)
if(type(q)==glue_node)
{delete_glue_ref(glue_ptr(q));
glue_ptr(q)= right_skip;
subtype(q)= right_skip_code+1;add_glue_ref(right_skip);
goto done;
}
else{if(type(q)==disc_node)
/*918:*/
#line 17415 "dummy.w"

{t= replace_count(q);
/*919:*/
#line 17423 "dummy.w"

if(t==0)r= link(q);
else{r= q;
while(t> 1)
{r= link(r);decr(t);
}
s= link(r);
r= link(s);link(s)= null;
flush_node_list(link(q));set_replace_count(q,0);
}

/*:919*/
#line 17417 "dummy.w"
;
if(post_break(q)!=null)/*920:*/
#line 17437 "dummy.w"

{s= post_break(q);
while(link(s)!=null)s= link(s);
link(s)= r;r= post_break(q);post_break(q)= null;post_disc_break= true;
}

/*:920*/
#line 17418 "dummy.w"
;
if(pre_break(q)!=null)/*921:*/
#line 17446 "dummy.w"

{s= pre_break(q);link(q)= s;
while(link(s)!=null)s= link(s);
pre_break(q)= null;q= s;
}

/*:921*/
#line 17419 "dummy.w"
;
link(q)= r;disc_break= true;
}

/*:918*/
#line 17406 "dummy.w"

else if((type(q)==math_node)||(type(q)==kern_node))width(q)= 0;
}
else{q= temp_head;
while(link(q)!=null)q= link(q);
}
/*922:*/
#line 17452 "dummy.w"

r= new_glue(right_skip);link(r)= link(q);link(q)= r;q= r

/*:922*/
#line 17412 "dummy.w"
;
done:

/*:917*/
#line 17386 "dummy.w"
;
/*923:*/
#line 17459 "dummy.w"

r= link(q);link(q)= null;q= link(temp_head);link(temp_head)= r;
if(left_skip!=zero_glue)
{r= new_glue(left_skip);
link(r)= q;q= r;
}

/*:923*/
#line 17387 "dummy.w"
;
/*925:*/
#line 17485 "dummy.w"

if(cur_line> last_special_line)
{cur_width= second_width;cur_indent= second_indent;
}
else if(par_shape_ptr==null)
{cur_width= first_width;cur_indent= first_indent;
}
else{cur_width= mem[par_shape_ptr+2*cur_line].sc;
cur_indent= mem[par_shape_ptr+2*cur_line-1].sc;
}
adjust_tail= adjust_head;just_box= hpack(q,cur_width,exactly);
shift_amount(just_box)= cur_indent

/*:925*/
#line 17388 "dummy.w"
;
/*924:*/
#line 17466 "dummy.w"

if(first_line)
{pointer p= happend_to_vlist(just_box);
uint32_t pos= hposition(p);
store_map(p,pos,line_offset);
first_line= false;
}
else
append_to_vlist(just_box,line_offset);
if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null

/*:924*/
#line 17390 "dummy.w"
;
/*926:*/
#line 17505 "dummy.w"

if(cur_line+1!=best_line)
{pen= inter_line_penalty;
if(cur_line==prev_graf+1)pen= pen+club_penalty;
if(cur_line+2==best_line)pen= pen+final_widow_penalty;
if(disc_break)pen= pen+broken_penalty;
if(pen!=0)
{r= new_penalty(pen);store_map(r,node_pos,next_offset);
link(tail)= r;tail= r;
}
}

/*:926*/
#line 17391 "dummy.w"


/*:916*/
#line 17330 "dummy.w"
;
incr(cur_line);cur_p= next_break(cur_p);
if(cur_p!=null)if(!post_disc_break)
/*915:*/
#line 17359 "dummy.w"

{r= temp_head;
loop{q= link(r);
if(q==cur_break(cur_p))goto done1;


if(is_char_node(q))goto done1;
if(non_discardable(q))goto done1;
if(type(q)==kern_node)if(subtype(q)!=explicit)goto done1;
r= q;
}
done1:if(r!=temp_head)
{link(r)= null;flush_node_list(link(temp_head));
link(temp_head)= q;
}
}

/*:915*/
#line 17333 "dummy.w"
;
}while(!(cur_p==null));
if((cur_line!=best_line)||(link(temp_head)!=null))
confusion(/*1728:*/
#line 26407 "dummy.w"
557
/*:1728*/
#line 17336 "dummy.w"
);

prev_graf= best_line-1;
}

/*:913*//*931:*/
#line 17616 "dummy.w"

/*:931*//*979:*/
#line 18429 "dummy.w"

#ifdef INIT
#endif

/*:979*/
#line 16092 "dummy.w"


void line_break(int final_widow_penalty,pointer par_ptr)
{scaled x= cur_list.hs_field;
/*897:*/
#line 17004 "dummy.w"

bool auto_breaking;
pointer prev_p;
pointer q,r,s;
internal_font_number f;

/*:897*//*929:*/
#line 17599 "dummy.w"


/*:929*/
#line 16096 "dummy.w"

set_line_break_params();
/*844:*/
#line 16117 "dummy.w"

link(temp_head)= par_ptr;

/*:844*//*858:*/
#line 16328 "dummy.w"

no_shrink_error_yet= true;
check_shrinkage(left_skip);check_shrinkage(right_skip);
q= left_skip;r= right_skip;background[1]= width(q)+width(r);
background[2]= 0;background[3]= 0;background[4]= 0;background[5]= 0;
background[2+stretch_order(q)]= stretch(q);
background[2+stretch_order(r)]= background[2+stretch_order(r)]+stretch(r);
background[6]= shrink(q)+shrink(r);

/*:858*//*867:*/
#line 16472 "dummy.w"

minimum_demerits= awful_bad;
minimal_demerits[tight_fit]= awful_bad;
minimal_demerits[decent_fit]= awful_bad;
minimal_demerits[loose_fit]= awful_bad;
minimal_demerits[very_loose_fit]= awful_bad;

/*:867*//*883:*/
#line 16735 "dummy.w"

if(par_shape_ptr==null)
if(hang_indent==0)
{last_special_line= 0;second_width= x;
second_indent= 0;
}
else/*884:*/
#line 16746 "dummy.w"

{last_special_line= abs(hang_after);
if(hang_after<0)
{first_width= x-abs(hang_indent);
if(hang_indent>=0)first_indent= hang_indent;
else first_indent= 0;
second_width= x;second_indent= 0;
}
else{first_width= x;first_indent= 0;
second_width= x-abs(hang_indent);
if(hang_indent>=0)second_indent= hang_indent;
else second_indent= 0;
}
}

/*:884*/
#line 16741 "dummy.w"

else QUIT("parshape not yet implemented");
if(looseness==0)easy_line= last_special_line;
else easy_line= max_halfword

/*:883*/
#line 16098 "dummy.w"
;
/*898:*/
#line 17014 "dummy.w"

threshold= pretolerance;
if(threshold>=0)
{
#ifdef STAT
if(tracing_paragraphs> 0)
{print_nl("@firstpass");}
#endif

second_pass= false;final_pass= false;
}
else{threshold= tolerance;second_pass= true;
final_pass= (emergency_stretch<=0);

#ifdef STAT
#endif

}
loop{if(threshold> inf_bad)threshold= inf_bad;
/*899:*/
#line 17068 "dummy.w"

q= get_node(active_node_size);
type(q)= unhyphenated;fitness(q)= decent_fit;
link(q)= last_active;break_node(q)= null;
line_number(q)= prev_graf+1;total_demerits(q)= 0;link(active)= q;
do_all_six(store_background);
passive= null;printed_node= temp_head;pass_number= 0;
font_in_short_display= null_font

/*:899*/
#line 17033 "dummy.w"
;
cur_p= link(temp_head);auto_breaking= true;
prev_p= cur_p;
while((cur_p!=null)&&(link(active)!=last_active))
/*901:*/
#line 17104 "dummy.w"

{if(is_char_node(cur_p))
/*902:*/
#line 17136 "dummy.w"

{prev_p= cur_p;
do{f= font(cur_p);
act_width= act_width+char_width(f)(char_info(f)(character(cur_p)));
cur_p= link(cur_p);
}while(!(!is_char_node(cur_p)));
}

/*:902*/
#line 17106 "dummy.w"
;
switch(type(cur_p)){
case hlist_node:case vlist_node:case rule_node:act_width= act_width+width(cur_p);break;
case whatsit_node:/*1408:*/
#line 25258 "dummy.w"

adv_past(cur_p)

/*:1408*/
#line 17109 "dummy.w"
break;
case glue_node:{/*903:*/
#line 17147 "dummy.w"

if(auto_breaking)
{if(is_char_node(prev_p))try_break(0,unhyphenated);
else if(precedes_break(prev_p))try_break(0,unhyphenated);
else if((type(prev_p)==kern_node)&&(subtype(prev_p)!=explicit))
try_break(0,unhyphenated);
}
check_shrinkage(glue_ptr(cur_p));q= glue_ptr(cur_p);
act_width= act_width+width(q);
active_width[2+stretch_order(q)]= 
active_width[2+stretch_order(q)]+stretch(q);
active_width[6]= active_width[6]+shrink(q)

/*:903*/
#line 17111 "dummy.w"
;
}break;
case kern_node:if(subtype(cur_p)==explicit)kern_break
else act_width= act_width+width(cur_p);break;
case ligature_node:{f= font(lig_char(cur_p));
act_width= act_width+char_width(f)(char_info(f)(character(lig_char(cur_p))));
}break;
case disc_node:/*904:*/
#line 17163 "dummy.w"

{if(!is_auto_disc(cur_p)||second_pass||final_pass)
{s= pre_break(cur_p);disc_width= 0;
if(s==null)try_break(ex_hyphen_penalty,hyphenated);
else{do{/*905:*/
#line 17183 "dummy.w"

if(is_char_node(s))
{f= font(s);
disc_width= disc_width+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
disc_width= disc_width+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
disc_width= disc_width+width(s);break;
default:confusion(/*1726:*/
#line 26401 "dummy.w"
555
/*:1726*/
#line 17195 "dummy.w"
);

}

/*:905*/
#line 17167 "dummy.w"
;
s= link(s);
}while(!(s==null));
act_width= act_width+disc_width;
try_break(hyphen_penalty,hyphenated);
act_width= act_width-disc_width;
}
}
r= replace_count(cur_p);s= link(cur_p);
while(r> 0)
{/*906:*/
#line 17199 "dummy.w"

if(is_char_node(s))
{f= font(s);
act_width= act_width+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
act_width= act_width+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
act_width= act_width+width(s);break;
default:confusion(/*1727:*/
#line 26404 "dummy.w"
556
/*:1727*/
#line 17211 "dummy.w"
);

}

/*:906*/
#line 17177 "dummy.w"
;
decr(r);s= link(s);
}
prev_p= cur_p;cur_p= s;goto done5;
}

/*:904*/
#line 17118 "dummy.w"

case math_node:{auto_breaking= (subtype(cur_p)==after);kern_break;
}break;
case penalty_node:try_break(penalty(cur_p),unhyphenated);break;
case mark_node:case ins_node:case adjust_node:do_nothing;break;
default:confusion(/*1725:*/
#line 26398 "dummy.w"
554
/*:1725*/
#line 17123 "dummy.w"
);

}
prev_p= cur_p;cur_p= link(cur_p);
done5:;}

/*:901*/
#line 17039 "dummy.w"
;
if(cur_p==null)
/*909:*/
#line 17235 "dummy.w"

{try_break(eject_penalty,hyphenated);
if(link(active)!=last_active)
{/*910:*/
#line 17245 "dummy.w"

r= link(active);fewest_demerits= awful_bad;
do{if(type(r)!=delta_node)if(total_demerits(r)<fewest_demerits)
{fewest_demerits= total_demerits(r);best_bet= r;
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet)

/*:910*/
#line 17238 "dummy.w"
;
if(looseness==0)goto done;
/*911:*/
#line 17259 "dummy.w"

{r= link(active);actual_looseness= 0;
do{if(type(r)!=delta_node)
{line_diff= line_number(r)-best_line;
if(((line_diff<actual_looseness)&&(looseness<=line_diff))||
((line_diff> actual_looseness)&&(looseness>=line_diff)))
{best_bet= r;actual_looseness= line_diff;
fewest_demerits= total_demerits(r);
}
else if((line_diff==actual_looseness)&&
(total_demerits(r)<fewest_demerits))
{best_bet= r;fewest_demerits= total_demerits(r);
}
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet);
}

/*:911*/
#line 17240 "dummy.w"
;
if((actual_looseness==looseness)||final_pass)goto done;
}
}

/*:909*/
#line 17042 "dummy.w"
;
/*900:*/
#line 17077 "dummy.w"

q= link(active);
while(q!=last_active)
{cur_p= link(q);
if(type(q)==delta_node)free_node(q,delta_node_size);
else free_node(q,active_node_size);
q= cur_p;
}
q= passive;
while(q!=null)
{cur_p= link(q);
free_node(q,passive_node_size);
q= cur_p;
}

/*:900*/
#line 17043 "dummy.w"
;
if(!second_pass)
{
#ifdef STAT
if(tracing_paragraphs> 0)print_nl("@secondpass");
#endif
threshold= tolerance;second_pass= true;final_pass= (emergency_stretch<=0);
}
else{
#ifdef STAT
if(tracing_paragraphs> 0)
print_nl("@emergencypass");
#endif
background[2]= background[2]+emergency_stretch;final_pass= true;
}
}
done:
#ifdef STAT
#endif

/*:898*/
#line 16099 "dummy.w"
;
/*912:*/
#line 17283 "dummy.w"

post_line_break(final_widow_penalty)

/*:912*/
#line 16101 "dummy.w"
;
/*900:*/
#line 17077 "dummy.w"

q= link(active);
while(q!=last_active)
{cur_p= link(q);
if(type(q)==delta_node)free_node(q,delta_node_size);
else free_node(q,active_node_size);
q= cur_p;
}
q= passive;
while(q!=null)
{cur_p= link(q);
free_node(q,passive_node_size);
q= cur_p;
}

/*:900*/
#line 16102 "dummy.w"
;
hrestore_param_list();
}

/*:843*//*1006:*/
#line 18934 "dummy.w"


#define ensure_vbox(N) 

extern void freeze_page_specs(small_number s);
extern pointer vert_break(pointer p,scaled h,scaled d);
extern void hship_out(pointer p);

stream_t*streams;

extern scaled hvsize;

/*1010:*/
#line 19020 "dummy.w"

scaled best_height_plus_depth;


/*:1010*//*1019:*/
#line 19222 "dummy.w"

pointer page_tail;
uint8_t page_contents;
scaled page_max_depth;
pointer best_page_break;
int least_page_cost;
scaled best_size;

/*:1019*//*1022:*/
#line 19304 "dummy.w"

scaled page_so_far[7];
scaled page_depth;
int insert_penalties;

/*:1022*/
#line 18946 "dummy.w"


pointer prune_page_top(pointer p)
{pointer prev_p;
pointer q;
prev_p= temp_head;link(temp_head)= p;
while(p!=null)
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:/*1007:*/
#line 18967 "dummy.w"

{temp_ptr= new_spec(pointer_def[glue_kind][split_top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;link(prev_p)= q;link(q)= p;

if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
p= null;
}

/*:1007*/
#line 18955 "dummy.w"
break;
case whatsit_node:case mark_node:case ins_node:{prev_p= p;p= link(prev_p);
}break;
case glue_node:case kern_node:case penalty_node:{q= p;p= link(q);link(q)= null;
link(prev_p)= p;flush_node_list(q);
}break;
default:confusion(/*1731:*/
#line 26416 "dummy.w"
560
/*:1731*/
#line 18961 "dummy.w"
);

}
return link(temp_head);
}

/*:1006*//*1008:*/
#line 18992 "dummy.w"

pointer vert_break(pointer p,scaled h,scaled d)

{
pointer prev_p;

pointer q,r;
int pi;
int b;
int least_cost;
pointer best_place;
scaled prev_dp;
small_number t;
prev_p= p;
least_cost= awful_bad;do_all_six(set_height_zero);prev_dp= 0;
loop{/*1011:*/
#line 19028 "dummy.w"

if(p==null)pi= eject_penalty;
else/*1012:*/
#line 19043 "dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{
cur_height= cur_height+prev_dp+height(p);prev_dp= depth(p);
goto not_found;
}
case whatsit_node:/*1411:*/
#line 25267 "dummy.w"

goto not_found

/*:1411*/
#line 19049 "dummy.w"
;
case glue_node:if(precedes_break(prev_p))pi= 0;
else goto update_heights;break;
case kern_node:{if(link(p)==null)t= penalty_node;
else t= type(link(p));
if(t==glue_node)pi= 0;else goto update_heights;
}break;
case penalty_node:pi= penalty(p);break;
case mark_node:case ins_node:goto not_found;
default:confusion(/*1732:*/
#line 26419 "dummy.w"
561
/*:1732*/
#line 19058 "dummy.w"
);

}

/*:1012*/
#line 19032 "dummy.w"
;
/*1013:*/
#line 19064 "dummy.w"

if(pi<inf_penalty)
{/*1014:*/
#line 19078 "dummy.w"

if(cur_height<h)
if((active_height[3]!=0)||(active_height[4]!=0)||
(active_height[5]!=0))b= 0;
else b= badness(h-cur_height,active_height[2]);
else if(cur_height-h> active_height[6])b= awful_bad;
else b= badness(cur_height-h,active_height[6])

/*:1014*/
#line 19066 "dummy.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)b= pi;
else if(b<inf_bad)b= b+pi;
else b= deplorable;
if(b<=least_cost)
{best_place= p;least_cost= b;
best_height_plus_depth= cur_height+prev_dp;
}
if((b==awful_bad)||(pi<=eject_penalty))goto done;
}

/*:1013*/
#line 19034 "dummy.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto not_found;
update_heights:/*1015:*/
#line 19090 "dummy.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
active_height[2+stretch_order(q)]= 
active_height[2+stretch_order(q)]+stretch(q);
active_height[6]= active_height[6]+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found in box being split");
r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
cur_height= cur_height+prev_dp+width(q);prev_dp= 0

/*:1015*/
#line 19037 "dummy.w"
;
not_found:if(prev_dp> d)
{cur_height= cur_height+prev_dp-d;
prev_dp= d;
}

/*:1011*/
#line 19009 "dummy.w"
;
prev_p= p;p= link(prev_p);
}
done:return best_place;
}

/*:1008*//*1027:*/
#line 19389 "dummy.w"

void freeze_page_specs(small_number s)
{page_contents= s;
page_goal= hvsize;page_max_depth= max_depth;
page_depth= 0;do_all_six(set_page_so_far_zero);
least_page_cost= awful_bad;

}

/*:1027*//*1035:*/
#line 19478 "dummy.w"

bool hbuild_page(void)
{
pointer p;
pointer q,r;
int b,c;
int pi;
if(link(contrib_head)==null)return false;
do{resume:p= link(contrib_head);
/*1038:*/
#line 19518 "dummy.w"

/*1041:*/
#line 19546 "dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:if(page_contents<box_there)
/*1042:*/
#line 19567 "dummy.w"

{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
link(q)= p;link(contrib_head)= q;goto resume;
}

/*:1042*/
#line 19550 "dummy.w"

else/*1043:*/
#line 19577 "dummy.w"

{page_total= page_total+page_depth+height(p);
page_depth= depth(p);
goto contribute;
}

/*:1043*/
#line 19551 "dummy.w"
break;
case whatsit_node:/*1410:*/
#line 25264 "dummy.w"

goto contribute

/*:1410*/
#line 19552 "dummy.w"
;
case glue_node:if(page_contents<box_there)goto done1;
else if(precedes_break(page_tail))pi= 0;
else goto update_heights;break;
case kern_node:if(page_contents<box_there)goto done1;
else if(link(p)==null)return false;
else if(type(link(p))==glue_node)pi= 0;
else goto update_heights;break;
case penalty_node:if(page_contents<box_there)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
case ins_node:happend_insertion(p);goto contribute;
default:confusion(/*1743:*/
#line 26452 "dummy.w"
572
/*:1743*/
#line 19563 "dummy.w"
);

}

/*:1041*/
#line 19522 "dummy.w"
;
/*1046:*/
#line 19605 "dummy.w"

if(pi<inf_penalty)
{/*1048:*/
#line 19649 "dummy.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

/*:1048*/
#line 19608 "dummy.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
else c= b;
if(insert_penalties>=10000)c= awful_bad;


if(c<=least_page_cost)
{best_page_break= p;best_size= page_goal;
least_page_cost= c;
r= link(page_ins_head);
while(r!=page_ins_head)
{best_ins_ptr(r)= last_ins_ptr(r);
r= link(r);
}
}
if((c==awful_bad)||(pi<=eject_penalty))
{hloc_set_next(best_page_break);
if(p==best_page_break)best_page_break= null;
hpack_page();
hfill_page_template();
return true;
}
}

/*:1046*/
#line 19525 "dummy.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto contribute;
update_heights:/*1045:*/
#line 19590 "dummy.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
page_so_far[2+stretch_order(q)]= 
page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
r= new_spec(q);shrink_order(r)= normal;fast_delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
page_total= page_total+page_depth+width(q);page_depth= 0

/*:1045*/
#line 19528 "dummy.w"
;
contribute:/*1044:*/
#line 19583 "dummy.w"

if(page_depth> page_max_depth)
{page_total= 
page_total+page_depth-page_max_depth;
page_depth= page_max_depth;
}

/*:1044*/
#line 19529 "dummy.w"
;
/*1039:*/
#line 19534 "dummy.w"

link(page_tail)= p;page_tail= p;
link(contrib_head)= link(p);link(p)= null;goto done

/*:1039*/
#line 19530 "dummy.w"
;
done1:/*1040:*/
#line 19538 "dummy.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p)

/*:1040*/
#line 19531 "dummy.w"
;
done:

/*:1038*/
#line 19489 "dummy.w"
;
}while(!(link(contrib_head)==null));
/*1036:*/
#line 19497 "dummy.w"

if(nest_ptr==0)tail= contrib_head;
else contrib_tail= contrib_head

/*:1036*/
#line 19491 "dummy.w"
;
return false;
}

/*:1035*//*1049:*/
#line 19657 "dummy.w"

void happend_insertion(pointer p)
{uint8_t n;
scaled delta,h,w;
pointer q,r;
if(page_contents==empty)freeze_page_specs(inserts_only);
n= subtype(p);r= page_ins_head;
while(n>=subtype(link(r)))r= link(r);
n= qo(n);
if(subtype(r)!=qi(n))
/*1050:*/
#line 19688 "dummy.w"

{q= get_node(page_ins_node_size);link(q)= link(r);link(r)= q;r= q;
subtype(r)= qi(n);type(r)= inserting;ensure_vbox(n);
if(box(n)==null)height(r)= 0;
else height(r)= height(box(n))+depth(box(n));
best_ins_ptr(r)= null;
q= skip(n);
if(count(n)==1000)h= height(r);
else h= x_over_n(height(r),1000)*count(n);
page_goal= page_goal-h-width(q);
page_so_far[2+stretch_order(q)]= page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage inserted from stream %d",n);
}

/*:1050*/
#line 19668 "dummy.w"
;
if(type(r)==split_up)insert_penalties= insert_penalties+float_cost(p);
else{last_ins_ptr(r)= p;
delta= page_goal-page_total-page_depth+page_shrink;

if(count(n)==1000)h= height(p);
else h= x_over_n(height(p),1000)*count(n);
if(((h<=0)||(h<=delta))&&(height(p)+height(r)<=dimen(n)))
{page_goal= page_goal-h;height(r)= height(r)+height(p);
}
else/*1051:*/
#line 19714 "dummy.w"

{if(count(n)<=0)w= max_dimen;
else{w= page_goal-page_total-page_depth;
if(count(n)!=1000)w= x_over_n(w,count(n))*1000;
}
if(w> dimen(n)-height(r))w= dimen(n)-height(r);
q= vert_break(ins_ptr(p),w,depth(p));
height(r)= height(r)+best_height_plus_depth;

if(count(n)!=1000)
best_height_plus_depth= x_over_n(best_height_plus_depth,1000)*count(n);
page_goal= page_goal-best_height_plus_depth;
type(r)= split_up;broken_ptr(r)= q;broken_ins(r)= p;
if(q==null)insert_penalties= insert_penalties+eject_penalty;
else if(type(q)==penalty_node)insert_penalties= insert_penalties+penalty(q);
}

/*:1051*/
#line 19678 "dummy.w"
;
}
}

/*:1049*//*1056:*/
#line 19803 "dummy.w"

void hpack_page(void)
{
pointer p,q,r,s;
pointer prev_p;
uint8_t n;
bool wait;
pointer save_split_top_skip;
#if 0
print_str("\npage_head:\n");
show_box(link(page_head));
print_str("\nstream 0:\n");
show_box(streams[0].p);
print_str("\nstream 1:\n");
show_box(streams[1].p);
#endif
if(box(0)!=null)
{flush_node_list(box(0));box(0)= null;}
insert_penalties= 0;
save_split_top_skip= split_top_skip;
/*1060:*/
#line 19889 "dummy.w"

{r= link(page_ins_head);
while(r!=page_ins_head)
{if(best_ins_ptr(r)!=null)
{n= qo(subtype(r));ensure_vbox(n);
if(box(n)==null)box(n)= new_null_box();
p= box(n)+list_offset;
while(link(p)!=null)p= link(p);
last_ins_ptr(r)= p;
}
r= link(r);
}
}

/*:1060*/
#line 19823 "dummy.w"
;
q= hold_head;link(q)= null;prev_p= page_head;p= link(prev_p);
while(p!=best_page_break)
{if(type(p)==ins_node)
{/*1062:*/
#line 19915 "dummy.w"

{r= link(page_ins_head);
while(subtype(r)!=subtype(p))r= link(r);
if(best_ins_ptr(r)==null)wait= true;
else{wait= false;s= last_ins_ptr(r);link(s)= ins_ptr(p);
if(best_ins_ptr(r)==p)
/*1063:*/
#line 19931 "dummy.w"

{if(type(r)==split_up)
if((broken_ins(r)==p)&&(broken_ptr(r)!=null))
{while(link(s)!=broken_ptr(r))s= link(s);
link(s)= null;
split_top_skip= split_top_ptr(p);
ins_ptr(p)= prune_page_top(broken_ptr(r));
if(ins_ptr(p)!=null)
{temp_ptr= vpack(ins_ptr(p),natural);
height(p)= height(temp_ptr)+depth(temp_ptr);
free_node(temp_ptr,box_node_size);wait= true;
}
}
while(link(s)!=null)s= link(s);
best_ins_ptr(r)= null;
n= qo(subtype(r));
temp_ptr= list_ptr(box(n));
free_node(box(n),box_node_size);
streams[n].p= temp_ptr;
streams[n].t= s;
}

/*:1063*/
#line 19922 "dummy.w"

else{while(link(s)!=null)s= link(s);
last_ins_ptr(r)= s;
}
}
/*1064:*/
#line 19953 "dummy.w"

link(prev_p)= link(p);link(p)= null;
if(wait)
{link(q)= p;q= p;incr(insert_penalties);
}
else{delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);
}
p= prev_p

/*:1064*/
#line 19928 "dummy.w"
;
}

/*:1062*/
#line 19828 "dummy.w"
;
}
prev_p= p;p= link(prev_p);
}
split_top_skip= save_split_top_skip;
/*1059:*/
#line 19867 "dummy.w"

if(p!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;
else contrib_tail= page_tail;
link(page_tail)= link(contrib_head);
link(contrib_head)= p;
link(prev_p)= null;
}
streams[0].p= link(page_head);link(page_head)= null;page_tail= page_head;
streams[0].t= prev_p;
if(q!=hold_head)
{link(q)= link(contrib_head);
link(contrib_head)= link(hold_head);
}

/*:1059*/
#line 19834 "dummy.w"
;
/*1061:*/
#line 19903 "dummy.w"

r= link(page_ins_head);
while(r!=page_ins_head)
{q= link(r);free_node(r,page_ins_node_size);r= q;
}
link(page_ins_head)= page_ins_head

/*:1061*/
#line 19835 "dummy.w"
;
}

/*:1056*//*1188:*/
#line 21807 "dummy.w"


void hdisplay(pointer p,pointer a,bool l)
{
scaled x;
uint32_t offset= node_pos-node_pos1;
{scaled w;
scaled l;
scaled s;
pointer p;
pointer q;
internal_font_number f;
int n;
scaled v;
scaled d;

if(head==tail)
{pop_nest();w= -max_dimen;x= cur_list.hs_field;offset= 0;
}
else{pointer par_ptr= link(head);
pop_nest();
store_map(par_ptr,node_pos,0);
line_break(display_widow_penalty,par_ptr);
x= cur_list.hs_field;
/*1189:*/
#line 21840 "dummy.w"

v= shift_amount(just_box)+2*dimen_def[quad_no];w= -max_dimen;
p= list_ptr(just_box);
while(p!=null)
{/*1190:*/
#line 21857 "dummy.w"

reswitch:if(is_char_node(p))
{f= font(p);d= char_width(f)(char_info(f)(character(p)));
goto found;
}
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{d= width(p);goto found;
}
case ligature_node:/*677:*/
#line 13040 "dummy.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:677*/
#line 21865 "dummy.w"

case kern_node:case math_node:d= width(p);break;
case glue_node:/*1191:*/
#line 21879 "dummy.w"

{q= glue_ptr(p);d= width(q);
if(glue_sign(just_box)==stretching)
{if((glue_order(just_box)==stretch_order(q))&&
(stretch(q)!=0))
v= max_dimen;
}
else if(glue_sign(just_box)==shrinking)
{if((glue_order(just_box)==shrink_order(q))&&
(shrink(q)!=0))
v= max_dimen;
}
if(subtype(p)>=a_leaders)goto found;
}

/*:1191*/
#line 21868 "dummy.w"
break;
case whatsit_node:/*1407:*/
#line 25254 "dummy.w"
d= 0

/*:1407*/
#line 21869 "dummy.w"
;break;
default:d= 0;
}

/*:1190*/
#line 21845 "dummy.w"
;
if(v<max_dimen)v= v+d;
goto not_found;
found:if(v<max_dimen)
{v= v+d;w= v;
}
else{w= max_dimen;goto done;
}
not_found:p= link(p);
}
done:

/*:1189*/
#line 21833 "dummy.w"
;
}

/*1192:*/
#line 21897 "dummy.w"

if(par_shape_ptr==null)
if((hang_indent!=0)&&
(((hang_after>=0)&&(prev_graf+2> hang_after))||
(prev_graf+1<-hang_after)))
{l= x-abs(hang_indent);
if(hang_indent> 0)s= hang_indent;else s= 0;
}
else{l= x;s= 0;
}
else{n= info(par_shape_ptr);
if(prev_graf+2>=n)p= par_shape_ptr+2*n;
else p= par_shape_ptr+2*(prev_graf+2);
s= mem[p-1].sc;l= mem[p].sc;
}

/*:1192*/
#line 21836 "dummy.w"
;
pre_display_size= w;display_width= l;display_indent= s;
}

/*:1188*//*1243:*/
#line 22563 "dummy.w"

{/*1241:*/
#line 22546 "dummy.w"

pointer b;
scaled w;
scaled z;
scaled e;
scaled q;
scaled d;
scaled s;
small_number g1,g2;
pointer r;
pointer t;

/*:1241*/
#line 22564 "dummy.w"

adjust_tail= adjust_head;b= hpack(p,natural);p= list_ptr(b);
t= adjust_tail;adjust_tail= null;
w= width(b);z= display_width;s= display_indent;
if(a==null)
{e= 0;q= 0;
}
else{e= width(a);q= e+math_quad;
}
if(w+q> z)
/*1245:*/
#line 22602 "dummy.w"

{if((e!=0)&&((w-total_shrink[normal]+q<=z)||
(total_shrink[fil]!=0)||(total_shrink[fill]!=0)||
(total_shrink[filll]!=0)))
{free_node(b,box_node_size);
b= hpack(p,z-q,exactly);
}
else{e= 0;
if(w> z)
{free_node(b,box_node_size);
b= hpack(p,z,exactly);
}
}
w= width(b);
}

/*:1245*/
#line 22575 "dummy.w"
;
/*1246:*/
#line 22626 "dummy.w"

d= half(z-w);
if((e> 0)&&(d<2*e))
{d= half(z-w-e);
if(p!=null)if(!is_char_node(p))if(type(p)==glue_node)d= 0;
}

/*:1246*/
#line 22577 "dummy.w"
;
/*1247:*/
#line 22639 "dummy.w"

tail_append(new_penalty(pre_display_penalty));
store_map(tail,node_pos,offset);
if((d+s<=pre_display_size)||l)
{g1= above_display_skip_no;g2= below_display_skip_no;
}
else{g1= above_display_short_skip_no;
g2= below_display_short_skip_no;
}
if(l&&(e==0))
{shift_amount(a)= s;append_to_vlist(a,offset);
tail_append(new_penalty(inf_penalty));store_map(tail,node_pos,offset);
}
else{tail_append(new_glue(pointer_def[glue_kind][g1]));store_map(tail,node_pos,offset);}

/*:1247*/
#line 22578 "dummy.w"
;
/*1248:*/
#line 22654 "dummy.w"

if(e!=0)
{r= new_kern(z-w-e-d);
if(l)
{link(a)= r;link(r)= b;b= a;d= 0;
}
else{link(b)= r;link(r)= a;
}
b= hpack(b,natural);
}
shift_amount(b)= s+d;append_to_vlist(b,offset)

/*:1248*/
#line 22579 "dummy.w"
;
/*1249:*/
#line 22666 "dummy.w"

if((a!=null)&&(e==0)&&!l)
{tail_append(new_penalty(inf_penalty));
shift_amount(a)= s+z-width(a);
append_to_vlist(a,offset);
g2= 0;
}
if(t!=adjust_head)
{link(tail)= link(adjust_head);tail= t;
}
tail_append(new_penalty(post_display_penalty));
offset= (hpos-hstart)+1-node_pos;
store_map(tail,node_pos,offset);
if(g2> 0){tail_append(new_glue(pointer_def[glue_kind][g2]));store_map(tail,node_pos,offset);}

/*:1249*/
#line 22580 "dummy.w"
;
prev_graf= prev_graf+3;
cur_list.bs_pos= hpos+node_pos;
push_nest();mode= hmode;
}
}

/*:1243*/
