

#include <iostream>
#include <pthread.h>

#include <stdlib.h>
#include <semaphore.h>


using namespace std;


       

void *berber(void*);
void *musteri(void*);

int koltukAdet;
int musteriAdet;
int ayrilanMusteri = 0;

sem_t semKoltuk;    
sem_t semMusteri;     
sem_t semBerber;  

int bakilanMusteri;
int  varOlanMusteri;
int sira;




int main()
{
	
    cout<<"Bekleme icin koltuk sayisi girin:";
    cin>>koltukAdet;
    cout<<"Musteri sayisini girin: ";
    cin>>musteriAdet;

    bakilanMusteri=0;
    varOlanMusteri=0;
    
	sem_init(&semKoltuk,0,1); 
 sem_init(&semMusteri,0,0);
    sem_init(&semBerber,0,0);
    
    
    
 pthread_t berberThread;           
pthread_t musterilerThreads[musteriAdet];

 
   
    
     if(musteriAdet>0)
     { pthread_create(&berberThread, NULL, berber, NULL); 
     	cout<<"\nMusteri var, berber uyandirildi"<<endl;
	 }
 
    
     for (int i = 0; i <musteriAdet; i++){
    sira=i+1; 
     
	  //pthread_create(&musterilerThreads[i], NULL, musteri, NULL); 
	  	  pthread_create(&musterilerThreads[i], NULL, musteri, &sira); 
		  
	   	cout<<sira<<".musteri dukkana girdi"<<endl;
		   //cout<<musterilerThreads[i]<<".musteri dukkana girdi"<<endl;
int uretimZamani;
		   uretimZamani=(rand() % 3) + 1;
		   sleep(uretimZamani);
        
	}
       
 
sleep(20);
   
        
      
        
         cout<<"\n\n-Berbere Gelen Musteri Analizi-\n";
         cout<<"---------------------------------------"<<endl;
        
         cout<<musteriAdet<<" musteriden " <<bakilanMusteri<<" sac kesimi yapildi"<<endl;
         cout<<ayrilanMusteri<<" musteri yer olmadigi icin ayrilmak zorunda kaldi"<<endl;
    
    exit(0);


}





void *berber(void*)

 {
 	
    int calismaZamani;

       


   while(1) {
    //if(musteriAdet==0)
    //{
    //	   cout<<"\nMusteri yok, berber uyuyor.\n";
        //    sem_wait(&musteriler);
          //  cout<<"Musteri geldi ve berberi uyandirdi, tiras basladi.\n";
	//}
	
   
      if(musteriAdet-(bakilanMusteri+ayrilanMusteri)==0)
  {
  	 
    cout<<"\nMusteri yok, berber uyuyor.\n";
     sem_wait(&semBerber);
     //sem_wait(&semKoltuk);
     sleep(3);
}

	else
	{
		

  sem_wait(&semMusteri);
	    sem_wait(&semKoltuk);

	 
	  
       
	    koltukAdet ++;
	  
 
	    calismaZamani = (rand() % 1) + 2;
	    cout<<"\nBerber yeni bir musteri aldi ve sac kesimi "<< calismaZamani<<" saniye surecek";
	   
	  cout<<"\tBos koltuk sayisi:"<<koltukAdet<<endl;
       	 sleep(calismaZamani);
       	 
       	 
       	 
       	
	    sem_post(&semKoltuk);
	   
	  sem_post(&semBerber);
    
	  
  

   	 
   	    
   		}
 
sleep(3);
    } 
     
}




void *musteri(void*sira)
{
	
	int konum = *(int *)sira;
 int beklemeSuresi;
  int yerVarsa = 1;
  //  while(yerVarsa == 1) {
		   
		   	    sem_wait(&semKoltuk);
		   	    
		   	     if(koltukAdet <= 0){
	      

		  sem_post(&semKoltuk); 
	       
	        beklemeSuresi = (rand() % 3) + 1;
	        cout<<konum<<".musteri"<<" yer olmadigi icin sacini kestirmeden ayrildi"<<endl;
            ayrilanMusteri++;
            
		    
		   
	       sleep(beklemeSuresi);
	    }
	      
		   
		   
		   else{
		  

		
           
		    koltukAdet --;
		 varOlanMusteri++;
		 //pthread_self()
		    //cout<<varOlanMusteri+bakilanMusteri<<".musteri koltuga oturdu ";
		    cout<<konum<<".musteri koltuga oturdu ";
		    		
		    
		  cout<<"\tBos koltuk sayisi:"<<koltukAdet;
		  cout<<"  Var Olan Musteri Sayisi:"<<varOlanMusteri;
		  cout<<"  Bakilan Musteri Sayisi:"<<bakilanMusteri<<endl;
          sleep(1);

		  
   		 sem_post(&semKoltuk);
   		    sem_post(&semMusteri);
   		sem_wait(&semBerber);
		  sleep(1);
			cout<<konum<<".musteri sacini kestirdi ve dukkandan ayrildi"<<endl;
           //cout<<bakilanMusteri+1<<".musteri sacini kestirdi ve dukkandan ayrildi"<<endl;
            varOlanMusteri--;
        		bakilanMusteri ++;
        	
         //yerVarsa = 0;

		    
	   // }
		   
	   
	}
	pthread_exit(0);
	 
}
