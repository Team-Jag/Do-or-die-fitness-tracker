class Campaign {
  private:
    String name;
    String description;

  public:
    Campaign(String name_in, String description_in) {
      name = name_in;
      description = description_in;
      }

      String getName() {
        return name;
      }

      String getDescription() {
        return description;
      }
  
};

