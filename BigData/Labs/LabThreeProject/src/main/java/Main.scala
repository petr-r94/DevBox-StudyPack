import org.apache.spark._
import org.apache.spark.SparkContext._
import org.apache.spark.SparkConf
import org.tartarus.snowball.SnowballStemmer
import org.tartarus.snowball.ext.russianStemmer
import org.apache.log4j._
import org.apache.spark.rdd._
import scala.io._
import scala.collection.mutable.ListBuffer

object Main {
  val stemmer = new russianStemmer()

  def printRDD(counts: RDD[(String, Int)], n: Int) {
    counts.take(n).foreach(println)
  }

  def printSRDD(counts: RDD[String], n: Int) {
    counts.take(n).foreach(println)
  }

  def printStopList(fileName: String) {
    println("=== Stop List loaded... ===")
    getStopList(fileName).foreach(println)
  }

  def getSparkContext_Linux(): SparkContext = {
    val conf = new SparkConf().setAppName("ThreeLab").setMaster("local")
    return new SparkContext(conf)
  }

  def removePunct(words: RDD[String]): RDD[String] = {
    val regex = """[\p{Punct}]"""
    return words.map(_.replaceAll(regex, ""))
  }

  def getStopList(fileName: String): Array[String] = {
    val stopList = Source.fromURL(getClass.getResource(fileName))
    return stopList.getLines().toArray
  }

  def getTop(counts: RDD[(String, Int)], n: Int): Array[(String, Int)] = {
    println("\n=== Top " + n.toString() + "... ===")
    val top = counts.sortBy(_._2, ascending = false)
    return top.take(n)
  }

  def getAntiTop(counts: RDD[(String, Int)], n: Int): Array[(String, Int)] = {
    println("\n=== AntiTop " + n.toString() + "... ===")
    val top = counts.sortBy(_._2, ascending = true)
    return top.take(n)
  }

  def runWordCount(sc: SparkContext, inputPath: String, stopListName: String): RDD[(String, Int)] = {
    printStopList(stopListName)
    println("=== WordCount Started... ===")
    val text = sc.textFile(inputPath)
    val words = removePunct(text.flatMap(line => line.split(" ")))
    val cleanWords = words.filter(x => !(getStopList(stopListName)
      .contains(x.toLowerCase)))
    val wordCounts = cleanWords.map(word => (word, 1)).reduceByKey(_ + _)
    printRDD(wordCounts, 100)
    //wordCounts.foreach(println)
    return wordCounts
  }

  def stemWord(stemmer: russianStemmer, word: String): String = {
    stemmer.setCurrent(word)
    stemmer.stem()
    stemmer.getCurrent()
  }

  def stemWords(words: RDD[(String, Int)]): RDD[(String,(String,Int))] = {
    return words.map(x => (stemWord(stemmer, x._1), x))
  }

  def runStemmer(sc: SparkContext, data: RDD[(String, Int)]): RDD[(String, Int)] = {
    println("\n=== Stemming Started... ===")
    val words = data.map(x => x._1)
// Transform (word, N) -> (stem, (word, N))
    val stems = stemWords(data)
    stems.take(100).foreach(println)
// Transform (stem, (word, N)) -> (stem, List[(word, N)])
    val listStems = stems.groupByKey().map(x =>
      (x._1, x._2.map(y => y._1).toList, x._2.map(y => y._2).sum)
    )
    listStems.take(50).foreach(println)
    
    println("\n=== Extend Table... ===")
    //fullRDD.take(100).foreach(println)
    val stemRDD = stems.map(stems => (stems._1 , 1)).reduceByKey(_ + _)
    return stemRDD
  }

  def main(args: Array[String]): Unit = {
    val sc = getSparkContext_Linux()
    LogManager.getRootLogger().setLevel(Level.WARN)
    val textPath = "src/main/resources/var_09.txt"
    val wc: RDD[(String, Int)] = runWordCount(sc, textPath, "stopList.txt")
    getTop(wc, 50).foreach(println)
    getAntiTop(wc, 50).foreach(println)
    val swc = runStemmer(sc, wc)
    getTop(swc, 50).foreach(println)
    getAntiTop(swc, 50).foreach(println)
  }
}

/* Неэффективный алгоритм
    val base: List[String] = words.collect.toList
    val extendRDD: RDD[(String, (Int, List[String]))] =
      fullRDD.map {
        case (stem, n) =>
          (stem, (n, base.filter(x => (stemWord(stemmer, x).equals(stem)))))
      }
*/
  
