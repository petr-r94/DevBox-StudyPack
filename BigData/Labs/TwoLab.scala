

object TwoLab extends App {

  def cleanerText(str: String): String = {
    val clr = Set(',', '.', '!', '?', ':')
    return str.filterNot(x => clr(x))
  }

  def catchWords(str: String): Array[String] = {
    return str.split(" ").filter(_.length > 1)
  }

  val text = "Жизнь легка, а ананас ананас большой? В мире правят ананас и кузнечики! В общем, такие вот дела"
  val clearText = cleanerText(text)

  val words: List[String] = catchWords(clearText).map(_.capitalize).toList.distinct.sortWith(_ < _)
  println("INPUT TEXT: " + text + "\n")
  println("RESULT: " + "\n")
  words.foreach(println)

}

