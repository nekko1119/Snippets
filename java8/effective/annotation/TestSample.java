package java8.effective.annotation;


public class TestSample {
  @Test
  public static void m1() {
  }

  public static void m2() {
  }
  @Test
  public static void m3() {
    throw new RuntimeException("Hoge");
  }

  public static void m4() {
  }

  @Test
  public void m5() {
  }

  public static void m6() {
  }

  @Test
  public static void m7() {
    throw new RuntimeException("Foo");
  }

  public static void m8() {
  }
}