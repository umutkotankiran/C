/*

	NESTED STRUCTURE

	struct Data {
		int ival;
		struct Nec {
			int a, b, c;
		}x;
	};

	veya aşağıdaki gibi yazılabilir

	struct Nec {
		int a, b, c;
	};

	struct Data {
		int ival;
		struct Nec x;
	};

	------------------------------------------------

	struct Data {
		int ival;
		struct Nec {
			int a, b, c;
		};
	};

	int main()
	{
		struct Data b; // struct Data nerede tanımlıysa, struct nec te orada tanımlıdır.
		struct Nec a; 
	}

	-----------------------------------------------------
	-----------------------------------------------------

struct Data {
	int ival;
	struct Nec {
		int a, b, c;
	}x;
};

int main()
{
	struct Data mydata;
	mydata.x.a;   // bildirim yukarıdaki gibi olsaydı bu şekilde kullanabilirdik.

	//c11 den sonra standart hale gelen eskiden extension olarak verilen özellik şu.
	// struct data da x ile tanımlanan değişken olmasaydı.
}

-------------------------------------------------------------
//aşağıdaki gibi sanki struct elemanı gibi erişilebilyor artık
struct Data {
	int ival;
	struct Nec {
		int a, b, c;
	};
};

int main()
{
	struct Data mydata;
	mydata.ival;
	mydata.a; // struct data nın içinde değişken verilmeden tanımlanan struct Nec in 
	mydata.b;	// elemanları aslında bunlar ama değişken verilmemiş, bu şekilde erişilir.
}

C++ ile C arasın farklılıklar çok bu tarafta.


----------------------------------------------------

NOT:  BİR STRUCT TÜRÜNÜN ELEMANI KENDİ TÜRÜNDEN OLAMAZ AMA KENDİ ADRESİ TÜRÜNDEN OLUR.
ÇÜNKÜ ADRES İFADESİNİN SİZEOF DEĞERİ BELLİ.

struct data{
	int a;
	struct data * ptr;
};
bu olur 
ama 
struct data x; olmaz.



----------------------------------------------------------
----------------------------------------------------------

	LINKED LIST

	En çok kullanılan veri yapısı dinamik diziydi.Bu ondan farklı

	singly linked list -> ileri gidilebiliyor.kendinden sonraki veriyi tutan düğümün
	adresini tutar ama kendinden öncekini tutamaz.

	doubly linked list - > hem ileri hemde geri gidilebiliyor.içerisinde nex ve prev isimli
	2 adet pointer var.daha fazla yer kaplar singly ye göre.

	-------------------------------------------

	// burada internet gitti tekrar et.

	Linked list Dezavantajları / Avantajları
	
	1 - Bellek kullanımı
	--------------------
	100 elemanlı bir int    sizeof(100*int) -> 400byte
	ama 
	
	100 elemanlı bir int    sizeof(100*int) + (100 * singly list ptr size)  -> 800 byte
	+ bir de header size var. çok daha fazla 800 den.
	
	Hatta doubly linked list olursa 1200 byte + header size lar -> 1200 den fazla yer kaplar.

	2 - Fragmante olmuş bir blokta bağlı listeyi büyütmek daha kolay olabilir.
	dinamik dizi olsaydı dizi 1.5 veya 2 katına çıkacağı için daha zor olur.

	3 - Dinamik dizide öğeye erişmek constant time.
		Bağlı listede 15. ye erişmek için ilk 14 ünü dolaşmak gerekiyor.

	4 - Bağlı listede ekleme veya silme işlemi constant time da yapılabilir.
		Dinamik dizide ise ortaya bir eleman eklemek için tüm diziyi 
		kaydırmak gerekiyor ve bunun içinde copy işlemi yapmak gerekiyor.

	SİNGLY DE SON ELEMANIN POİNTERI NULL PTR DIR
	DOUBLY DE SON->next VE İLK->prev ELEMANIN POİNTERI NULL PTR DIR.

	Günümüzde en popüler olan yapı ise CACHE mekanizması.

	Ramden veriye erişmek yerine, bunların bir kısmını daha hızlı işlem yapılan bir
	bellek alanına aktarılıyor.Bunada cache deniyor. Memoryden erişmek yavaş, önbellekten
	erişmek ise daha hızı.

	İhtiyaç duyduğum nesne cache de ise buna cache hit, değilse cache miss deniyor.

	Dinamik dizi burada bağlı listeye göre daha avantajlı olabiliyor.

	Dinamik dizilerde verileri takas etmenin yolu, verileri takas etmekten geçiyor.
	Bağlı listelerde ise sadece düğümlerdeki pointerları takas ederek gerçekleştirebiliyoruz.

	----------------------------------------------------------------------------------
	----------------------------------------------------------------------------------
	----------------------------------------------------------------------------------
	----------------------------------------------------------------------------------
	----------------------------------------------------------------------------------

	AMACIMIZ BAĞLI LİSTELERİ İMPLEMENTE ETMEK DEĞİL.
	SADECE HANDLE A HAZIRLIK YAPACAĞIZ VE SONRADA HANDLE KODLAYACAĞIZ.
	HANDLE LAR SADECE BAĞLI LİSTELERDE YOK.HERYERDE KULLANILABİLİYOR.

	---------------------------------------------------------------------
	---------------------------------------------------------------------
	---------------------------------------------------------------------

	Dilediğimiz zaman baştan ekleyeceğimiz bir veri yapısı olsun

	hasan	ayşe	mehmet			şeklinde ekleme ve silme baştan yapılacak.
			hasan	ayşe
					hasan 

	==========================================================================
	==========================================================================
	==========================================================================


	TEST KODU 1
	-----------
	
	Employee emp;
	randomize();

	for (int i = 0; i < 10; i++)
	{
		set_employee_random(&emp); // baştan ekliyor ama en son eklediği en başta olacak
		print_employee(&emp);		
		push_front(&emp);
	}
	(void)getchar();
	printf("Listede %d calisan var\n", get_size()); //10
	display_list();		// burada en son eklenilenin en başta olduğu görülür
	make_empty();
	printf("Listede %d calisan var\n", get_size()); //0

	---------------------------------------------------------------
	---------------------------------------------------------------

	TEST KODU 2
	-----------
	size_t n;
	printf("Listeye kac calisan eklenecek\n");
	(void)scanf("%zu", &n);

	Employee e;
	randomize();

	clock_t start = clock();
	for (size_t i = 0; i < n; i++)
	{
		set_employee_random(&e);
		push_front(&e);
	}
	clock_t end = clock();

	printf("Listede %f saniyede %d calisan eklendi",
		(double)(end-start)/ CLOCKS_PER_SEC,get_size());

	(void)_getch(); // turbo c den kalma. conio.h içinde var.
	display_list();
	make_empty();


	----------------------------------------------------------------------
	----------------------------------------------------------------------

	TEST KODU 3
	
	randomize();
	Employee e;
	int n = rand() % 20 + 10; // listeye kaç eleman ekleneceği runtime da belli olacak

	for (int i = 0; i < n; i++)
	{
		set_employee_random(&e);
		push_front(&e);
	}

	while (!isempty())
	{
		printf("Listede %d calisan var\n", get_size());
		display_list();
		pop_front();
		_getch();
		system("cls");
	}


	======================================================================
	======================================================================
	======================================================================
	======================================================================

	BU KÜTÜPHANE ÇOK KULLANILIR BİR KÜTÜPHANE DEĞİL.
	SADECE 1 LİSTE ÜZERİNDE İŞLEMLER YAPIYOR.
	HALBUKİ CLİENT KOD İSTEDİĞİ ZAMAN BİR LİSTE OLUŞTURABİLMELİ.
	HER LİSTE İÇİN GPFİRST VE GPCOUNT DEĞERLERİ FARKLI OLMALI.

	BURADA HANDLE TEKNİĞİ KULLANILIYOR.
	BU BİR GİZLEME MEKANİZMASI GİBİ ÇALIŞIYOR.

	ORTAK KULLANILACAK DATALAR BİR YAPININ NESNELERİ YAPILIR.

	struct data{
		int d1,d2,d3,d4;
	};

	SONRA FONKSİYONA BU YAPI TÜRÜNÜN ADRESİ GÖNDERİLİR.
	BU İŞLEM

	OPEN 
	CREATE İŞLEMİ DİYE GEÇER

	DAHA SONRA CLOSE VEYA DESTROY EDİLECEK BU VERİLER.

	OOP DİLLERDE BUNLARA CONSTRUCTOR VEYA DESTRUCTOR DENİYOR.

	---------------------------------------------------------------------------
	---------------------------------------------------------------------------
	---------------------------------------------------------------------------
	---------------------------------------------------------------------------

	KÜTÜPHANEDE YAPILAN DEĞİŞİKLİKLER EMPLOYEELİST.C VE H DOSYALARINDA VAR.NOT ALINDI.
	KÜTÜPHANELERE BAK.
	
	#define		NLIST	1000

	int main()
	{

		ListHandle a[NLIST];
		Employee emp;

		randomize();

		for (int i = 0; i < NLIST; ++i)
		{
			a[i] = create_list();
			int n = rand() % 10 + 10;
			while (n--)
			{
				set_employee_random(&emp);
				push_front(a[i], &emp);
			}
		}

		for (int i = 0; i < NLIST; ++i)
		{
			printf("%d. listede  %d calisan var\n", i + 1, get_size(a[i]));
			display_list(a[i]);
			_getch();
			system("cls");
		}

		for (int i = 0; i < NLIST; i++)
		{
			destroy_list(a[i]);
		}
	}


	-----------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------

	İŞLEMLERİNDE DE HANDLE KULLANILIYOR.
	FPRİNTF
	FREAD
	FPUTC
	FGETC
	FSEEK
	
	HEPSİNDE HANDLE SİSTEMİ VAR. FILE * türünden parametreleri var.

	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================


	STRUCT ALNIGMENT PADDING

	Bellekte 1 byte a erişme diye birşey yok. işlemci 32 bit ise 32 bitlik veriye yani 4 byte,
	64 ise 8 bytelık veriye erişir.

	temel erişim birimi işlemcinin kaç bit olduğu bilgisidir.s

	daha önce konuşulmuştu.
	bir datanın bir kısmı bir bellek alanında, diğer kısmıda diğer bellek alanında olursa bunları birleştirmesi gerekir.
	Buda maliyetli bir işlem. BUnun yerine alignment yapıyor.

	char 1 byte heryere yerleştirir.

	short 2 byte. 2nin tamkatı olan yerlere yerleştirir.

	int 4 byte. 
	
	double 8 byte.

	C++ ta bu alignment requeiremnt değeri operatör ile elde ediliyor.

	C de extension olarak var.


	typedef struct {
		char cx;
		int ival;
		char cy;
	}Nec;   //mesela burası 6 byte değil 12 byte.

	
	 NEC İÇİN MEMORY DURUMU
	Eğer aşağıdaki gibi olsaydı çok maliyetli olurdu.
	Çünkü işlemci ivale erişmek için 2 defa erişim yapıp bunları birleştirmek zorunda

	
	| cx | ival  | ival  | ival  |||| ival  |  cy  |    |     ||||    |    |    |     |

	-------------------------------

	Peki ne olsaydı mantıklı olurdu.
	Aşağıdaki gibi olsaydı.İval 4 byte ve tek seferde bu 4 bytelık veriye erişebiliyor.
	Ayrıca birleştirme maliyeti de yok.

	| cx |   |   |   |||| ival   |  ival  |  ival  |  ival   |||| cy   |    |    |     |  yani bu şekilde memory düzeni oluşmuyor.

	Bellek bloğunda nesne içerisinde kalan ama bizim değerlerimizi tutmayan, sadece hazilama amacıyla kullanılan byte veya bytelar var.
	Bunlara padding bytes/hole deniyor.

	Yani aslında aşağıdaki gibi
	Padding bytes = PD

	| cx |  PD | PD  | PD  |||| ival   |  ival  |  ival  |  ival   |||| cy   |  PD  |  PD  | PD  |   = 12 byte eder.


	------------------------

	Yapu nesnesinin minimal yer kaplaması için padding bytesları minimize etmemiz lazım.
	bunun için büyük bytelı nesneleri struct içinde başta tanımlamak gerekir.

	typedef struct {
		int ival;
		char cx;
		char cy;
	}Nec;

	printf("%zu", sizeof(Nec)); = 8 yazar


	| ival   |  ival  |  ival  |  ival   |||| cx   |  cy  |  PD  | PD  |||| PD  |  PD | PD  | PD |  = burada ise son 4 bite gerek kalmadı
																									= 8 byte eder.
	
	NOT: ELEMANLAR BÜYÜKTEN KÜÇÜĞE SIRALANMALI. EN OPTİMUM DÜZEN BU ŞEKİLDE OLUŞUYOR.

	PADDİNG BYTELARIN FARKINDA DEĞİLSEK, CİDDİ HATA YAPILABİLİR.
	MESELA POİNTER ARİTMETİĞİ İLE YANLIŞ ELEMANA ERİŞMEK.

	typedef struct {
		char cx;
		int ival;
		char cy;
	}Nec;

	Nec nec = {'A',123567,'B'};

	char *p = &nec.x;


	printf("%d\n",*(int*)(p + 1)); // hatalı

	// burada p + 1 dersem bir sonraki nesneye erişirim diye düşünüyor.
	// *(int *)(p + 1) yaparım diyor :D:D ama halbuki paddings bytes ta şuanda :D    cx ten sonra hemen ival gelmiyor PD var:D
	// 	 bunun değerininde 123567 olacağını sanıyor. aslında PD den dolayı p + 1 değil !!!!!!!!!
	// p + 4 demem gerekir !!!!!!

	| cx |  PD | PD  | PD  |||| ival   |  ival  |  ival  |  ival   |||| cy   |  PD  |  PD  | PD  |

	printf("%d\n", *(int*)(p + 4));  // doğru

	-------------------------------------------------------------------
	-------------------------------------------------------------------

	STDDEF.H İÇİNDE OFFSETOF MACROSU VAR.
	offsetoff macrosu ile Undefined Behavior durumuna düşmeden, bir elemanın yapı nesnesi içindeki izafi konumunu elde edebiliriz.

	bizde manuel olarak yazıyoruz.
	orijinali küçük harfle yazılıyor.
	biz birinciyi büyük yazacağız

	Offsetof(type,member)
	type -> yapı türünü yazıyoruz
	member -> struct içindeki elemanların biri

	size_t türünden tamsayı değeri döner.
	yapının başlangıcı olan adresten ne kadar uzak olduğunu verir.
	

	ÖR:
	//default gelen offsetoff
	printf("offsetoff cx = %zu\n", offsetof(Nec, cx)); // başlangıçta yani 0.da
	printf("offsetoff ival = %zu\n", offsetof(Nec, ival)); // bir sonraki blokta 4
	printf("offsetoff cy = %zu\n", offsetof(Nec, cy));	// sonrasındaki blokta 8


	MANUEL NASIL YAZILIR.

	Offsetof(type,member)

	0 type * türüne cast edilir ------->   (type *)0
	bu nesnenin elemanına ok oper. ile eriş ------->   ((type *)0)->member // not: böyle bırakırsan UB
	sonrasında tekrar adresini alıyor ------->   &((type *)0)->member
	birde bu adresi size_t ye cast ediyor. -----> (size_t)&((type *)0)->member

	#define			Offsetof(type,member)		(size_t)&((type *)0)->member

	TAMAM AMA NE İŞE YARIYOR.
	BİR ÖĞENİN ADRESİNDEN DİĞERİNE ERİŞMEK İSTERTSEK,VEYA YAPI NESNESİNDEN BAŞKA BİR OBJEYE ERİŞMEK İSTERSEK KULLANILIR.
	
	typedef struct {
		char cx;
		int ival;
		char cy;
	}Nec;
	
	Nec nec;

	(int *)((char*)&nec + offsetof(Nec, ival)); // char adresinden int in adresine bu şekilde geçebiliriz.

	ÖR:

	Nec nec;
	nec.ival = 10;

	printf("%d", *((int*)((char*)&nec + offsetof(Nec, ival))));

	alignof(short); -> short 2 nin tamkatı olan yerlere yerleştirilebilir demek
	alignof(int); -> int 4 ün tamkatları olan adreslere yerleştirilebilir ...
 

	*/
